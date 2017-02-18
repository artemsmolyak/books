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

QLineEdit *EditDialog::getMainIdeaText() const
{
    return mainIdeaText;
}

void EditDialog::setMainIdeaText(QLineEdit *value)
{
    mainIdeaText = value;
}

EditDialog::EditDialog()
{
    //setSizePolicy(QSizePolicy::Minimum);
    resize(700, 700);



    QLabel * titleLable = new QLabel("title: ");
    titleText = new QLineEdit();

      QLabel * authorLable = new QLabel("authors: ");
      authorsText = new QLineEdit();

      QLabel * mainIdeaLable = new QLabel("main idea: ");
      mainIdeaText = new QLineEdit();


      picButton = new QPushButton;
      minSizePic.setWidth(150);
      minSizePic.setHeight(150);
      picButton->setMinimumSize(minSizePic);

      connect(picButton, SIGNAL(clicked(bool)), this, SLOT(addBookPic()));

      QLabel * genreLable = new QLabel("genre: ");
      genreCombobox = new QComboBox;

      QLabel * numPagesLable = new QLabel("number of pages: ");
      numberOfPagesText = new QLineEdit();

      QLabel * startReadLable = new QLabel("start: ");
      dateStart = new QDateEdit;

      QLabel * finishReadLable = new QLabel("finish: ");      
      finishReadLable->setAlignment(Qt::AlignRight);
      dateFinish = new QDateEdit;

      rate = new Assesment;

      QLabel * tagsLable = new QLabel("tags: ");
      tagsText = new QLineEdit();

      //Toolbar


      QAction * actionBold = new QAction(QIcon(":/picButtons/textbold.png"), "bold", this);
      connect(actionBold, SIGNAL(triggered(bool)), this, SLOT(actionBold()));
      QAction * actionCenter = new QAction(QIcon(":/picButtons/textcenter.png"), "center", this);
      connect(actionCenter, SIGNAL(triggered(bool)), this, SLOT(actionCenter()));
      QAction * actionItalic = new QAction(QIcon(":/picButtons/textitalic.png"), "italic", this);
      connect(actionItalic, SIGNAL(triggered(bool)), this, SLOT(actionItalic()));
      QAction * actionJustify = new QAction(QIcon(":/picButtons/textjustify.png"), "justify", this);
      connect(actionJustify, SIGNAL(triggered(bool)), this, SLOT(actionJustify()));
      QAction * actionLeft = new QAction(QIcon(":/picButtons/textleft.png"), "left", this);
      connect(actionLeft, SIGNAL(triggered(bool)), this, SLOT(actionLeft()));
      QAction * actionRight = new QAction(QIcon(":/picButtons/textright.png"), "right", this);
      connect(actionRight, SIGNAL(triggered(bool)), this, SLOT(actionRigth()));
      QAction * actionUnder = new QAction(QIcon(":/picButtons/textunder.png"), "under", this);
      connect(actionUnder, SIGNAL(triggered(bool)), this, SLOT(actionUnder()));


      QToolBar * toolBar = new QToolBar;
      toolBar->addAction(actionBold);
      toolBar->addAction(actionCenter);
      toolBar->addAction(actionItalic);
      toolBar->addAction(actionJustify);
      toolBar->addAction(actionLeft);
      toolBar->addAction(actionRight);
      toolBar->addAction(actionUnder);


      //review
      reviewText = new QPlainTextEdit;


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
      layout->addWidget(numberOfPagesText, 3,  3, 1, 1  );

      layout->addWidget(startReadLable, 4,  0, 1, 1  );
      layout->addWidget(dateStart, 4,  1, 1, 1  );

      layout->addWidget(finishReadLable, 4,  2, 1, 1  );
      layout->addWidget(dateFinish, 4,  3, 1, 1  );

      layout->addWidget(rate, 5,  1, 1, 4  );

      layout->addWidget(tagsLable, 6,  0, 1, 1  );
      layout->addWidget(tagsText, 6,  1, 1, 3  );

      layout->addWidget(picButton, 3, 4, 4, 4);


      //

      layout->addWidget(toolBar, 7,  0, 1, 4  );

      layout->addWidget(reviewText, 8,  0, 1, 8   );

      layout->addWidget(saveBtn, 10,  6, 1, 1 );
      layout->addWidget(cancelBtn, 10,  7, 1, 1  );


      setLayout(layout);

      connect(saveBtn, SIGNAL(clicked(bool)), this, SLOT(on_SaveButton_released()));
}

void EditDialog::setGenre(QList <QString> listGenre)
{
    int i = 0;
    for(QString item : listGenre)
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
    QPixmap * pixmap = new QPixmap(":/empty");
    if (pixmap->size().width() > minSizePic.width() ||
       pixmap->size().height() > minSizePic.height())
        *pixmap = pixmap->scaled(minSizePic.width(), minSizePic.height(), Qt::KeepAspectRatio);

    QIcon buttonIcon(*pixmap);
    picButton->setIcon(buttonIcon);
    picButton->setIconSize(pixmap->rect().size());
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

void EditDialog::actionBold()
{
qDebug() << "signal";
}

void EditDialog::actionCenter()
{
qDebug() << "signal";
}

void EditDialog::actionItalic()
{
qDebug() << "signal";
}

void EditDialog::actionJustify()
{
qDebug() << "signal";
}

void EditDialog::actionLeft()
{
qDebug() << "signal";
}

void EditDialog::actionRigth()
{
qDebug() << "signal";
}

void EditDialog::actionUnder()
{
qDebug() << "signal";
}

void EditDialog::addBookPic()
{
    qDebug() << "signal";
    QString fileName = QFileDialog::getOpenFileName(this,
                                                   tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));


    QPixmap * pixmap = new QPixmap(fileName);
    QSize minSize(150, 150);
    if (pixmap->size().width() > minSize.width() ||
       pixmap->size().height() > minSize.height())
        *pixmap = pixmap->scaled(minSize.width(), minSize.height(), Qt::KeepAspectRatio);

    QIcon buttonIcon(*pixmap);
    picButton->setIcon(buttonIcon);
    picButton->setIconSize(pixmap->rect().size());



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

        int genre = genreCombobox->currentIndex();

        int pages = numberOfPagesText->text().toInt();

        QDate dateS = dateStart->date();
        QDate dateF = dateFinish->date();

        QString tags = tagsText->text();
        QStringList tagsList = tags.split(",");

        QString  review = reviewText->toPlainText();

        QIcon icon = picButton->icon();
        QPixmap bookCoverPixmap = icon.pixmap(minSizePic);

        emit newItemIsReady(
                    Data(title, authors, mainIdea, rateInt, genre,
                         pages, dateS, dateF, tagsList,
                         review,  bookCoverPixmap)
                    );
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
