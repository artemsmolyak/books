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

EditDialog::EditDialog()
{
    //setSizePolicy(QSizePolicy::Minimum);
      resize(700, 700);



      QLabel * titleLable = new QLabel("title: ");
      QLineEdit * titleText = new QLineEdit();

      QLabel * authorLable = new QLabel("authors: ");
      QLineEdit * authorText = new QLineEdit();

      QLabel * mainIdeaLable = new QLabel("main idea: ");
      QLineEdit * mainIdeaText = new QLineEdit();


      picButton = new QPushButton;
      QSize minSize(150, 150);
      picButton->setMinimumSize(minSize);

      QPixmap * pixmap = new QPixmap(":/empty");
      if (pixmap->size().width() > minSize.width() ||
         pixmap->size().height() > minSize.height())
          *pixmap = pixmap->scaled(minSize.width(), minSize.height(), Qt::KeepAspectRatio);

      QIcon buttonIcon(*pixmap);
      picButton->setIcon(buttonIcon);
      picButton->setIconSize(pixmap->rect().size());
      connect(picButton, SIGNAL(clicked(bool)), this, SLOT(addBookPic()));

      QLabel * genreLable = new QLabel("genre: ");
      QComboBox * genreCombobox = new QComboBox;

      QLabel * numPagesLable = new QLabel("number of pages: ");
      QLineEdit * numberOfPagesText = new QLineEdit();

      QLabel * startReadLable = new QLabel("start: ");
      QDateEdit * dateStartText = new QDateEdit;

      QLabel * finishReadLable = new QLabel("finish: ");      
      finishReadLable->setAlignment(Qt::AlignRight);
      QDateEdit * dateFinishText = new QDateEdit;

      Assesment * rate = new Assesment;

      QLabel * tagsLable = new QLabel("tags: ");
      QLineEdit * tagsText = new QLineEdit();

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
      QPlainTextEdit * reviewText = new QPlainTextEdit;


      QPushButton * saveBtn =new QPushButton("save");
      QPushButton * cancelBtn = new QPushButton("cancel");


      QGridLayout * layout = new QGridLayout;
      layout->addWidget(titleLable, 0,  0,  1, 1  );
      layout->addWidget(titleText, 0,  1, 1, 7  );

      layout->addWidget(authorLable, 1,  0, 1, 1  );
      layout->addWidget(authorText, 1,  1, 1, 7  );

      layout->addWidget(mainIdeaLable, 2,  0, 1, 1  );
      layout->addWidget(mainIdeaText, 2,  1, 1, 7  );

      //
      layout->addWidget(genreLable, 3,  0, 1, 1  );
      layout->addWidget(genreCombobox, 3,  1, 1, 1 );

      layout->addWidget(numPagesLable, 3,  2, 1, 1  );
      layout->addWidget(numberOfPagesText, 3,  3, 1, 1  );

      layout->addWidget(startReadLable, 4,  0, 1, 1  );
      layout->addWidget(dateStartText, 4,  1, 1, 1  );

      layout->addWidget(finishReadLable, 4,  2, 1, 1  );
      layout->addWidget(dateFinishText, 4,  3, 1, 1  );

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
