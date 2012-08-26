#include "OptionsDialog.h"
#include "ui_OptionsDialog.h"
#include <QCryptographicHash>


OptionsDialog::OptionsDialog(QWidget *parent)
	: QDialog(parent), ui(new Ui::OptionsDialog)
{
	ui->setupUi(this);

	fillAction2ButtonMap();

	load();

	doubleKey=false;

	connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onClick(QAbstractButton*)));

	/*! Une tentative de solution */
	QSignalMapper* signalMapper = new QSignalMapper(this) ;
	connect(ui->buttonUp, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
	connect(ui->buttonDown, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
	connect(ui->buttonLeft, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
	connect(ui->buttonRight, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
	connect(ui->buttonJump, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
	connect(ui->buttonDrop, SIGNAL(clicked()), signalMapper, SLOT(map()));

	signalMapper->setMapping(ui->buttonUp, UP);
	signalMapper->setMapping(ui->buttonDown, DOWN);
	signalMapper->setMapping(ui->buttonLeft, LEFT);
	signalMapper->setMapping(ui->buttonRight, RIGHT);
	signalMapper->setMapping(ui->buttonJump, JUMP);
	signalMapper->setMapping(ui->buttonDrop, DROP);

	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(changeKey(int))) ;
}

OptionsDialog::~OptionsDialog()
{
	delete ui;
}

void OptionsDialog::onClick(QAbstractButton* button)
{
	if(ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok)
	{
		save();
	}

	else if(ui->buttonBox->standardButton(button) == QDialogButtonBox::RestoreDefaults)
	{
		config.defaultValues();
		refresh();
	}
}

void OptionsDialog::refresh()
{
	resetAllColor();

	ui->windowSizeComboBox->setCurrentIndex(config.getWindowSize());
	ui->seedLineEdit->setText(QVariant(config.getSeed()).toString());
	ui->FPSSpinBox->setValue(config.getFps());

	QMapIterator<Action,QPushButton*> i(m_actionToButtonMap);
	 while (i.hasNext()) {
		 i.next();
		 m_actionToButtonMap[(Action)i.key()]->setText(config.getKeyVal((Action)i.key()));
	 }

	checkDoubleKey();

	ui->viewDistanceSpinBox->setValue(config.getViewDistance());
	ui->smoothShadesCheckBox->setChecked(config.getSmoothShades());
	ui->antialiasingCheckBox->setChecked(config.getAntialiasing());
	ui->textureFilteringComboBox->setCurrentIndex(config.getTextureFiltering());
}

void OptionsDialog::load()
{
	config.loadDefaultConfigFile();
	refresh();
}

void OptionsDialog::save()
{
	config.setWindowSize((ClientConfiguration::WindowSize)ui->windowSizeComboBox->currentIndex());
	if(QString::number(ui->seedLineEdit->text().toInt()) == ui->seedLineEdit->text()) {
		config.setSeed(ui->seedLineEdit->text().toInt());
	}
	else {
		// Not a number : get an integer hash of the string as seed
		// Generate a 128 bits hash
		QByteArray hash = QCryptographicHash::hash(ui->seedLineEdit->text().toAscii(), QCryptographicHash::Md5);
		char* hashData = hash.data();
		// Get each 32 bits part in a int
		qint32 int1 = *reinterpret_cast<qint32*>(&hashData[0]);
		qint32 int2 = *reinterpret_cast<qint32*>(&hashData[4]);
		qint32 int3 = *reinterpret_cast<qint32*>(&hashData[8]);
		qint32 int4 = *reinterpret_cast<qint32*>(&hashData[12]);
		qint32 seed = int1 + int2 + int3 + int4;
		config.setSeed(seed);
	}
	config.setFps(ui->FPSSpinBox->value());
	config.setViewDistance(ui->viewDistanceSpinBox->value());
	config.setSmoothShades(ui->smoothShadesCheckBox->isChecked());
	config.setAntialiasing(ui->antialiasingCheckBox->isChecked());
	config.setTextureFiltering(ui->textureFilteringComboBox->currentIndex());
	config.save();
}

void OptionsDialog::changeKey(int action)
{
	if(!reallocation)
	{
		reallocation=true;
		reallocationKey=action;
		setButtonColor(BLUE,(Action)action);
	}
}

void OptionsDialog::keyPressEvent(QKeyEvent *event)
{
	if(reallocation)
	{
		reallocation=false;

		if(event->key()==Qt::Key_Space)
			config.setKey((Action)reallocationKey,Qt::Key_Space);
		else
			config.setKey((Action)reallocationKey,event->key());
		refresh();
	}
	checkDoubleKey();
}

void OptionsDialog::checkDoubleKey()
{
	doubleKey=false;
	QPushButton *okButton=ui->buttonBox->button(QDialogButtonBox::Ok);
	okButton->setEnabled(true);

	for(int i = 0; i < NBVAL; i++)
	{
		int comp = config.getKey((Action)i);
		for(int j = 0; j < NBVAL; j++)
		{
			if(comp == config.getKey((Action)j) && i!=j)
			{
				doubleKey=true;
				okButton->setEnabled(false);
				setButtonColor(RED,(Action)i);
				setButtonColor(RED,(Action)j);
			}
		}
	}
}

void OptionsDialog::setButtonColor(Color color, Action action)
{
	switch(color)
	{
	case RED:
		m_actionToButtonMap[action]->setStyleSheet("background-color:#ba0000;");
		break;
	case BLUE:
		m_actionToButtonMap[action]->setStyleSheet("background-color:#20acd6;");
		break;
	case DEFAULT:
		m_actionToButtonMap[action]->setStyleSheet("background-color:auto;");
		break;

	}
}

void OptionsDialog::resetAllColor()
{
	QMapIterator<Action,QPushButton*> i(m_actionToButtonMap);
	 while (i.hasNext()) {
		 i.next();
		 setButtonColor(DEFAULT,(Action)i.key());
	 }
}

void OptionsDialog::fillAction2ButtonMap()
{
	m_actionToButtonMap[UP] = ui->buttonUp;
	m_actionToButtonMap[DOWN] = ui->buttonDown;
	m_actionToButtonMap[LEFT] = ui->buttonLeft;
	m_actionToButtonMap[RIGHT] = ui->buttonRight;
	m_actionToButtonMap[JUMP] = ui->buttonJump;
	m_actionToButtonMap[DROP] = ui->buttonDrop;
}
