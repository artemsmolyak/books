#include "editdialog.h"
#include "QLineEdit"
#include "QComboBox"
#include "QPlainTextEdit"
#include "QDateEdit"
#include "assesment.h"
#include "QGridLayout"
#include "QPushButton"
#include "QLabel"
#include "QPixmap"
#include "QIcon"
#include "QGroupBox"
#include "QToolBar"
#include "QFileDialog"
#include "QDebug"
#include "QImageReader"
#include "QTextCharFormat"
#include "QtNetwork/QNetworkAccessManager"
#include "QNetworkReply"
#include "QLoggingCategory";
#include "QJsonDocument"
#include "QJsonArray"
#include "QMessageBox"

QLineEdit *EditDialog::getMainIdeaText() const
{
    return mainIdeaText;
}

void EditDialog::setMainIdeaText(QLineEdit *value)
{
    mainIdeaText = value;
}

void EditDialog::clearAll()
{
    typePic = "";

    picButton->setIcon(QPixmap(":/empty.png"));
    genreCombobox->setCurrentIndex(0);
    dateStart->setDate(QDate::currentDate());
    dateFinish->setDate(QDate::currentDate());
    rate->setAssesment(1);
    authorsText->setText("");
    mainIdeaText->setText("");
    titleText->setText("");
    numberOfPagesText->setText("");
    tagsText->setText("");
    reviewText->setPlainText("");

}


EditDialog::EditDialog()
{

//     QFile File(":/styles/QTDark.css"); //QTDark
//     if (File.open(QFile::ReadOnly))
//     {
//     QString StyleSheet = QLatin1String(File.readAll());
//      this->setStyleSheet(StyleSheet);
//     }
//     else
//     {
//         qDebug() << "!";
//     }



    //setSizePolicy(QSizePolicy::Minimum);
     resize(700, 700);
     idData = -1;


    QLabel * titleLable = new QLabel("title: ");
    titleText = new QLineEdit();

      QLabel * authorLable = new QLabel("authors: ");
      authorsText = new QLineEdit();

      QLabel * mainIdeaLable = new QLabel("main idea: ");
      mainIdeaText = new QLineEdit();


      picButton = new QPushButton;
      minSizePic.setWidth(widthPic);
      minSizePic.setHeight(heightPic);
      //picButton->setMinimumSize(minSizePic);

      connect(picButton, SIGNAL(clicked(bool)), this, SLOT(addBookPic()));

      QLabel * genreLable = new QLabel("genre: ");
      genreCombobox = new QComboBox;

      QLabel * numPagesLable = new QLabel("number of pages: ");
      numberOfPagesText = new QLineEdit();

      QLabel * startReadLable = new QLabel("start reading: ");
      dateStart = new QDateEdit;
      dateStart->setMinimumDate(QDate(1984, 01, 01));

      QLabel * finishReadLable = new QLabel("finish: ");      
      finishReadLable->setAlignment(Qt::AlignRight);
      dateFinish = new QDateEdit;

      rate = new Assesment;
      rate->setUseMouse(true);

      QLabel * tagsLable = new QLabel("tags: ");
      tagsText = new QLineEdit();

      //Toolbar
      actionBold = new QAction(QIcon(":/picButtons/textbold.png"), "bold", this);
      connect(actionBold, SIGNAL(triggered(bool)), this, SLOT(slotBold()));
      actionBold->setCheckable(true);


      actionItalic = new QAction(QIcon(":/picButtons/textitalic.png"), "italic", this);
      connect(actionItalic, SIGNAL(triggered(bool)), this, SLOT(slotItalic()));
      actionItalic->setCheckable(true);

      actionJustify = new QAction(QIcon(":/picButtons/textjustify.png"), "justify", this);
      connect(actionJustify, SIGNAL(triggered(bool)), this, SLOT(slotJustify()));
      actionJustify->setCheckable(true);
      actionLeft = new QAction(QIcon(":/picButtons/textleft.png"), "left", this);
      connect(actionLeft, SIGNAL(triggered(bool)), this, SLOT(slotLeft()));
      actionLeft->setCheckable(true);
      actionRight = new QAction(QIcon(":/picButtons/textright.png"), "right", this);
      connect(actionRight, SIGNAL(triggered(bool)), this, SLOT(slotRigth()));
      actionRight->setCheckable(true);
      actionCenter = new QAction(QIcon(":/picButtons/textcenter.png"), "center", this);
      connect(actionCenter, SIGNAL(triggered(bool)), this, SLOT(slotCenter()));
      actionCenter->setCheckable(true);

      actionUnder = new QAction(QIcon(":/picButtons/textunder.png"), "under", this);
      connect(actionUnder, SIGNAL(triggered(bool)), this, SLOT(slotUnder()));
      actionUnder->setCheckable(true);


      QToolBar * toolBar = new QToolBar;
      toolBar->addAction(actionBold);     
      toolBar->addAction(actionItalic);
      toolBar->addAction(actionUnder);

      toolBar->addAction(actionJustify);
      toolBar->addAction(actionCenter);
      toolBar->addAction(actionLeft);
      toolBar->addAction(actionRight);


      fontComboBox = new QFontComboBox;

      //review
      reviewText = new QTextEdit();


      QPushButton * saveBtn =new QPushButton("save");
      QPushButton * cancelBtn = new QPushButton("cancel");


      QGridLayout * layout = new QGridLayout;
      layout->addWidget(titleLable, 0,  0,  1, 1  );
      layout->addWidget(titleText, 0,  1, 1, 7  );

      layout->addWidget(authorLable, 1,  0, 1, 1  );
      layout->addWidget(authorsText, 1,  1, 1, 7  );

      layout->addWidget(mainIdeaLable, 2,  0, 1, 1  );
      layout->addWidget(mainIdeaText, 2,  1, 1, 7  );

      //
      layout->addWidget(genreLable, 3,  0, 1, 1  );
      layout->addWidget(genreCombobox, 3,  1, 1, 1 );

      layout->addWidget(numPagesLable, 3,  2, 1, 1  );
      layout->addWidget(numberOfPagesText, 3,  3, 1,  1  );

      layout->addWidget(startReadLable, 4,  0, 1, 1  );
      layout->addWidget(dateStart, 4,  1, 1, 1  );

      layout->addWidget(finishReadLable, 4,  2, 1, 1  );
      layout->addWidget(dateFinish, 4,  3, 1, 1  );

      layout->addWidget(rate, 5,  1, 1, 4  );

      layout->addWidget(tagsLable, 6,  0, 1, 1  );
      layout->addWidget(tagsText, 6,  1, 1, 3  );


      layout->addWidget(picButton, 3, 4, 4, 4);


      QPushButton * btnSearchPic = new QPushButton("Search");
      layout->addWidget(btnSearchPic, 7,  4, 1, 3);

      nextBtn = new QPushButton(">>");
      nextBtn->setEnabled(false);
      layout->addWidget(nextBtn, 7,  7, 1, 1);




      //

      layout->addWidget(toolBar, 7,  0, 1, 3  );
      layout->addWidget(fontComboBox, 7, 3, 1, 1);

      layout->addWidget(reviewText, 8,  0, 1, 8);

      layout->addWidget(saveBtn, 10,  6, 1, 1 );
      layout->addWidget(cancelBtn, 10,  7, 1, 1  );


      setLayout(layout);

       connect(saveBtn, SIGNAL(clicked(bool)), this, SLOT(on_SaveButton_released()));
       connect(btnSearchPic, SIGNAL(clicked(bool)), this, SLOT(searchPic()));



       //bing search
       picLoader = new QNetworkAccessManager(this);

       connect(picLoader, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(loadPicSlot(QNetworkReply*)));


       connect(nextBtn, SIGNAL(clicked(bool)), this, SLOT(showBingPicture()));

}

void EditDialog::closeEvent(QCloseEvent * e){
   clearAll();
   QWidget::closeEvent(e);
}

void EditDialog::showBingPicture()
{
    if (picBingNumber > 9 || tenPicturesFromBing.length() < picBingNumber)
               picBingNumber = 0;

qDebug() << "showBingPicture 1";
    QString urlPic = (QString)tenPicturesFromBing.at(picBingNumber++);
qDebug() << "2";

    QUrl url(urlPic);
    QString stringURL = url.fromPercentEncoding(urlPic.toUtf8());
    int index = stringURL.indexOf("=http");

    //qDebug() << "before " << stringURL;
    stringURL =  stringURL.remove(0, index + 1);
    //qDebug() << "after " << stringURL;

    index = stringURL.indexOf("&p=DevEx");
    //qDebug() << "before " << stringURL;
    stringURL =  stringURL.remove(index, stringURL.length() - 1);
    //qDebug() << "after " << stringURL;

    qDebug() << "url " << stringURL;

    url.setUrl(stringURL);
    QNetworkRequest request(url);
    picLoader->get(request);
}


void EditDialog::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionUnder->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void EditDialog::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = reviewText->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    cursor.mergeCharFormat(format);
    reviewText->mergeCurrentCharFormat(format);
}

void EditDialog::textAlign(QAction *a)
{
//    if (a == actionAlignLeft)
//        reviewText->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
//    else if (a == actionAlignCenter)
//         reviewText->setAlignment(Qt::AlignHCenter);
//    else if (a == actionAlignRight)
//         reviewText->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
//    else if (a == actionAlignJustify)
//         reviewText->setAlignment(Qt::AlignJustify);
}

void EditDialog::textItalic()
{
//    QTextCharFormat fmt;
//    fmt.setFontItalic(actionTextItalic->isChecked());
//    mergeFormatOnWordOrSelection(fmt);
}

void EditDialog::textBold()
{
//    QTextCharFormat fmt;
//    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
//    mergeFormatOnWordOrSelection(fmt);
}



void EditDialog::setGenre(QList<QString> genreList)
{
    qDebug() << "genre hash size" << genreList.size();
    genreCombobox->clear();

    int i = 0;
    for(QString item : genreList)
        genreCombobox->addItem(item);
}

void EditDialog::setStartDate()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QDate dateToday = dateTime.date();
    dateStart->setDate(dateToday);
}

void EditDialog::setFinishDate()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QDate dateToday = dateTime.date();
    dateFinish->setDate(dateToday);
}

void EditDialog::setPicDefault()
{
    pixmapPic.load(":/empty");

    QPixmap * pixmapForButton = new QPixmap(":/empty");

    if (pixmapForButton->size().width() > minSizePic.width() ||
       pixmapForButton->size().height() > minSizePic.height())
        *pixmapForButton = pixmapForButton->scaled(minSizePic.width(), minSizePic.height(), Qt::KeepAspectRatio);

    QIcon buttonIcon(*pixmapForButton);
    picButton->setIcon(buttonIcon);
    picButton->setIconSize(pixmapForButton->rect().size());
}

void EditDialog::reset()
{
//        ui->dateEdit->clear();
//        ui->titleEdit->clear();
//        ui->authorEdit->clear();
//        ui->assesmentWidget->setAssesment(0);
//        ui->bookCoverLabel->setPixmap(QPixmap("://empty.png"));
    //        ui->reviewEdit->clear();
}

void EditDialog::viewDataForEdit(Data data)
{
    setWindowTitle("Edit book");

    idData = data.getId();
    titleText->setText(data.getBookTitle());
    authorsText->setText(data.getAuthorsName());
    mainIdeaText->setText(data.getMainIdea());

    rate->setAssesment(data.getRateInt());

    genreCombobox->setCurrentIndex(data.getGenre() - 1);  //count from 1

    numberOfPagesText->setText(QString::number(data.getPages()));

    dateStart->setDate(data.getDateS());
    dateFinish->setDate(data.getDateF());

    tagsText->setText(data.getTagsList().join(", "));

    reviewText->setHtml(data.getReview());

    QPixmap picForButton = data.getBookCoverPixmap();
    pixmapPic =  data.getBookCoverPixmap();

    QSize sizePic = picForButton.rect().size();
    if (sizePic.width() > minSizePic.width() || sizePic.height() > minSizePic.height())
        sizePic = minSizePic;

    if (!picForButton)
    {
        picButton->setIcon(QPixmap(":/empty.png"));
        pixmapPic.load(":/empty.png");
    }
    else
    {
        picButton->setIcon(picForButton);
    }

    picButton->setIconSize(sizePic);

    typePic = data.getTypePic();

}

void EditDialog::slotBold()
{
    qDebug() << "signal Bold";

    QTextCharFormat fmt;
    fmt.setFontWeight(actionBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);

}

void EditDialog::slotCenter()
{
     reviewText->setAlignment(Qt::AlignHCenter);
}

void EditDialog::slotItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(actionItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void EditDialog::slotJustify()
{
 reviewText->setAlignment(Qt::AlignJustify);
}

void EditDialog::slotLeft()
{
   reviewText->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
}

void EditDialog::slotRigth()
{
reviewText->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
}

void EditDialog::slotUnder()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionUnder->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void EditDialog::slotTextAlign(QAction *a)
{
//    if (a == actionLeft)

//    else if (a == actionCenter)

//    else if (a == actionRight)

//    else if (a == actionJustify)

}

void EditDialog::addBookPic()
{
    qDebug() << "signal addBookPic";
    QString fileName = QFileDialog::getOpenFileName(this,
                                                   tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.jpeg  *.bmp)"));


    pixmapPic.load(fileName);
    QPixmap pixmapTmp(pixmapPic);

    QSize minSize(widthPic, heightPic);
    if (pixmapTmp.size().width() > minSize.width() ||
       pixmapTmp.size().height() > minSize.height())
        pixmapTmp = pixmapTmp.scaled(minSize.width(), minSize.height(), Qt::KeepAspectRatio);

    QIcon buttonIcon(pixmapTmp);
    picButton->setIcon(buttonIcon);
    picButton->setIconSize(pixmapTmp.rect().size());

    //save type
    typePic = getFileType(fileName);

}

QString EditDialog::getFileType(QString pathFilePic)
{
    QFileInfo fi(pathFilePic);
    return fi.suffix();
//    QImageReader reader(pathFilePic);
//    QByteArray nameArray = reader.format();
//    return QString::fromLatin1(nameArray.data());
}

void EditDialog::getNewItem(Data data)
{

}

void EditDialog::editItem(Data data)
{

}

void EditDialog::on_SaveButton_released()
{
    //if (mode == add)
    {
        setWindowTitle("Add book");

        QString title = titleText->text();
        QString  authors = authorsText->text();
        QString mainIdea = mainIdeaText->text();

        int rateInt = rate->getAssesment();

        int genre = genreCombobox->currentIndex() + 1;  //count from 1

        int pages = numberOfPagesText->text().toInt();

        QDate dateS = dateStart->date();
        QDate dateF = dateFinish->date();

        QString tags = tagsText->text();
        QStringList tagsList = tags.split(",");

        QString  review = reviewText->toHtml();


//        // -------------
//        QString filename="Data.txt";
//        QFile file( filename );
//        if ( file.open(QIODevice::ReadWrite) )
//        {
//            QTextStream stream( &file );
//            stream <<review;
//        }
//        file.close();
//        //

//         QIcon icon  = picButton->icon();

//         if (pixmapPic.isNull())
//         {
//             qDebug() << "!!!!!!!!!!!!!!!!!!!!!" ;
//         }

//         QSize size(widthPic, heightPic);
//         pixmapPic = icon.pixmap(size);


//        qDebug() << "pic size " << pixmapPic.width() << pixmapPic.height()
//                 << typePic;

        emit newItemIsReady(
                    Data(idData, title, authors, mainIdea, rateInt, genre,
                         pages, dateS, dateF, tagsList,
                         review,  pixmapPic, typePic, QDate())
                    );
        clearAll();
    }
    //else if (mode == edit)
//    {
//        QString assessment = QString::number(ui->assesmentWidget->getAssesment());
//        QString  author = ui->authorEdit->text();
//        QString  title  = ui->titleEdit->text();
//        QString   date = ui->dateEdit->text();
//        QString  review = ui->reviewEdit->toPlainText();
//        const QPixmap *bookCoverPix = ui->bookCoverLabel->pixmap();
//        emit editItemIsReady(Data(assessment, author, title, date, review, *bookCoverPix));
//    }
    this->hide();
    this->reset();
}

void EditDialog::searchPic()
{
    QString authorsForSearch = "book cover ";
    authorsForSearch += authorsText->text();
    authorsForSearch = authorsForSearch.toUtf8();

    QString titleForSearch = titleText->text().toUtf8();

    QString searchString ="https://api.cognitive.microsoft.com/"
                          "bing/v5.0/images/search?q=" + titleForSearch +
            " " + authorsForSearch + "&count=10" + "&offset=0&mkt=ru-ru&safeSearch=Moderate";

    //&nbsp

    QLoggingCategory::setFilterRules("qt.network.ssl.w arning=false");

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    qDebug() << "search "<<searchString;

    QUrl urlSearch(searchString);
    QNetworkRequest request(urlSearch);

    //request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "charset=utf-8");
    request.setRawHeader(QByteArray("Ocp-Apim-Subscription-Key"), QByteArray("f7c8c77ee00247ada569c026dae186df"));


    manager->get(request);
    //manager->get(QNetworkRequest(QUrl("https://www.google.ru/search?q=книга+марсианин&newwindow=1&source=lnms&tbm=isch")));
}



void EditDialog::replyFinished(QNetworkReply* reply)
{
    QString otvet;

    switch (reply->error())
    {
    case 0:
    {
        //        otvet = QString::fromUtf8(reply->readAll());
        //        qDebug() <<"otvet: "<< otvet;

        QStringList responseFromBing;

        QString strReply = QString::fromUtf8(reply->readAll());
        //qDebug() <<"reply "<<strReply;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["value"].toArray();

        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
            responseFromBing.append(obj["contentUrl"].toString());
            //propertyKeys.append(obj["key"].toString());
        }


        if (responseFromBing.length() == 0)
        {
            picButton->setIcon(QIcon(":/netu.jpg"));
            nextBtn->setEnabled(false);
        }
        else
        {
            tenPicturesFromBing = responseFromBing;
            picBingNumber = 0;
            showBingPicture();
            nextBtn->setEnabled(true);
        }
        break;
    }
    default:
        QMessageBox msgBox;
        msgBox.setText("Problems with searching. Try later");
        msgBox.exec();
        break;
    }
}

void EditDialog::loadPicSlot(QNetworkReply *reply)
{
//    qDebug() << "loadPicSlot";
//    QString otvet;


//        otvet = QString::fromUtf8(reply->readAll());
//        qDebug() << otvet;
//        break;

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QImage image = QImage::fromData(data);

        qDebug() <<"image size height "<< image.width()<<image.height();

        if (image.width() == 0 || image.height() == 0)
        {
            picButton->setIcon(QIcon(":/netu.jpg"));
        }
        else
        {
            int picNum = picBingNumber - 1;
             QString str= (QString)tenPicturesFromBing.at(picNum);
             QUrl url(str);
             QString path = url.fromPercentEncoding(str.toUtf8());
             int index = path.indexOf("=http");
             path =  path.remove(0, index + 1);
             index = path.indexOf("&p=DevEx");
             path =  path.remove(index, path.length() - 1);

             QFileInfo fi(path);
             typePic = fi.completeSuffix();

             qDebug() <<"path "<< path;

            pixmapPic = QPixmap::fromImage(image);

            pixmapPic.save("/home/artem/Downloads/pixmap.jpg");
            QIcon icon;
            icon.addPixmap(pixmapPic);
            picButton->setIcon(icon);
        }
    }
  }
