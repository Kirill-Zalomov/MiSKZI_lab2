#include "controller.h"
#include "ui_main_window.h"


Controller::Controller(QWidget *parent) : QMainWindow(parent) {
    this->ui = new Ui::Controller();
    this->ui->setupUi(this);
    this->moveWindowToCenterOfDisplay();

    QString executablePath = QCoreApplication::applicationDirPath();
    QString filePath = QDir(executablePath).filePath("ru_dictionary.txt");
    this->fillDictionaryWithContentFromFile(filePath);
}


Controller::~Controller() {
    delete this->ui;
}


void Controller::fillDictionaryWithContentFromFile(QFile fileWithDictionary) {
    this->dictionary.clear();
    if(!fileWithDictionary.exists() || !fileWithDictionary.open(QIODevice::ReadOnly)) {
        return;
    }

    QTextStream fileReader(&fileWithDictionary);
    while(!fileReader.atEnd()) {
        this->dictionary.append(fileReader.readLine());
    }
    fileWithDictionary.close();
}


QStringList Controller::getDictionary() const {
    return dictionary;
}


void Controller::setDictionary(const QStringList &newDictionary) {
    dictionary = newDictionary;
}


void Controller::moveWindowToCenterOfDisplay() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect rect = screen->geometry();
    QPoint centerPoint = rect.center();
    centerPoint.setX(centerPoint.x() - (this->width() / 2));
    centerPoint.setY(centerPoint.y() - this->height() / 2);
    this->move(centerPoint);
}


inline void Controller::setStatusBarText(const QString &text) {
    this->ui->labelStatusBar->setText(R"(  Строка состояния: )" + text);
}


bool Controller::validateFileToDecipher() {
    QString inputFileAbsolutePath = this->ui->lineEditInputFile->text();
    if(inputFileAbsolutePath.isEmpty()) {
        this->setStatusBarText(R"(Входной файл не выбран.)");
        return false;
    }

    QFile inputFile = QFile(this->ui->lineEditInputFile->text());
    if(!inputFile.exists()) {
        this->setStatusBarText(R"(Входной файл не существует.)");
        return false;
    }

    return true;
}


void Controller::on_buttonOpenFile_clicked() {
    QString inputFilePath;
    inputFilePath = QFileDialog::getOpenFileName(this, R"(Выбор файл)", QStandardPaths::writableLocation(QStandardPaths::HomeLocation), R"(Текстовые файлы (*.txt))");
    if(inputFilePath.isEmpty()) return;

    this->ui->lineEditInputFile->setText(inputFilePath);
    this->ui->lineEditInputFile->setCursorPosition(0);
    this->setStatusBarText(R"(Выбран входной файл.)");
}


void Controller::on_buttonDecypher_clicked() {
    if (!(this->validateFileToDecipher())) return;

    QString inputFileAbsolutePath = this->ui->lineEditInputFile->text();
    FileInteractor fileInteractor;
    ModifiedAtbashDecipher atbashDesipher;
    QString textFromInputFile = fileInteractor.readContentFromFile(inputFileAbsolutePath);

    QList<quint32> numberOfMatches(alphabetSize, 0);
    quint8 keyWithMaxValue = 0;
    quint32 maxMatches = 0;

    // Цикл декодирования и подсчета совпадений
    this->ui->labelFoundKey->setText("  Проверяемый ключ:");
    for (quint8 testKey = 0; testKey < alphabetSize; ++testKey) {
        QString decipheredText = atbashDesipher.decipher(textFromInputFile, testKey);
        MatchFinder matchFinder;
        numberOfMatches[testKey] = matchFinder.countMatches(decipheredText, this->getDictionary());

        // Обновление надписи с текущим ключом
        this->ui->labelKey->setText(QString("%1 (совпадений: %2)").arg(QString::number(testKey, 16).rightJustified(2, '0')).arg(QString::number(numberOfMatches[testKey])));
        QApplication::processEvents();

        // Обновление максимального значения и ключа
        if (numberOfMatches[testKey] > maxMatches) {
            maxMatches = numberOfMatches[testKey];
            keyWithMaxValue = testKey;
        }
    }

    // Обновление надписи с ключом с максимальным значением
    this->ui->labelFoundKey->setText("  Подобранный ключ:");
    this->ui->labelKey->setText(QString("%1").arg(QString::number(keyWithMaxValue, 16).rightJustified(2, '0')));

    // Декодирование с использованием ключа с максимальным значением
    QString resultText = atbashDesipher.decipher(textFromInputFile, keyWithMaxValue);
    fileInteractor.writeContentInFile(inputFileAbsolutePath, resultText, true);
}



