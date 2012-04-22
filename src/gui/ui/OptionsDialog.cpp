#include "OptionsDialog.h"
#include "ui_OptionsDialog.h"
#include <QDebug>

OptionsDialog::OptionsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OptionsDialog)
{
	ui->setupUi(this);

	configureMap();

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

	signalMapper->setMapping(ui->buttonUp, UP) ;
	signalMapper->setMapping(ui->buttonDown, DOWN) ;
	signalMapper->setMapping(ui->buttonLeft, LEFT) ;
	signalMapper->setMapping(ui->buttonRight, RIGHT) ;
	signalMapper->setMapping(ui->buttonJump, JUMP) ;

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
		config.reloadDefault();
		refresh();
	}
}

void OptionsDialog::refresh()
{
	resetAllColor();
	ui->seedLineEdit->setText(QVariant(config.getSeed()).toString());
	ui->FPSSpinBox->setValue(config.getFps());

	QMapIterator<Action,QPushButton*> i(ActionToButtonMap);
	 while (i.hasNext()) {
		 i.next();
		 ActionToButtonMap[(Action)i.key()]->setText(config.getKeyVal((ClientConfiguration::Action)i.key()));
	 }
	/*ui->buttonUp->setText(config.getKeyVal(ClientConfiguration::UP));
	ui->buttonLeft->setText(config.getKeyVal(ClientConfiguration::LEFT));
	ui->buttonDown->setText(config.getKeyVal(ClientConfiguration::DOWN));
	ui->buttonRight->setText(config.getKeyVal(ClientConfiguration::RIGHT));
	ui->buttonJump->setText(config.getKeyVal(ClientConfiguration::JUMP));*/
	checkKey();

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
	config.setSeed(ui->seedLineEdit->text().toInt());
	config.setFps(ui->FPSSpinBox->value());
	//config.setKey(ClientConfiguration::DOWN,32);
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
			config.setKey((ClientConfiguration::Action)reallocationKey,Qt::Key_Space);
		else
			config.setKey((ClientConfiguration::Action)reallocationKey,event->key());
		//ActionToButtonMap[(Action)reallocationKey]->setText(config.getKeyVal((ClientConfiguration::Action)reallocationKey));
		refresh();
	}
	checkKey();
	/*if(!doubleKey)
	{
		refresh();
	}*/

}

void OptionsDialog::checkKey()
{
	doubleKey=false;
	QPushButton *okButton=ui->buttonBox->button(QDialogButtonBox::Ok);
	okButton->setEnabled(true);

	for(int i=0;i<ClientConfiguration::NBVAL;i++)
	{
		int comp = config.getKey((ClientConfiguration::Action)i);
		for(int j=0;j<ClientConfiguration::NBVAL;j++)
		{
			if(comp == config.getKey((ClientConfiguration::Action)j) && i!=j)
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
		ActionToButtonMap[action]->setStyleSheet("background-color:#ba0000;");
		break;
	case BLUE:
		ActionToButtonMap[action]->setStyleSheet("background-color:#20acd6;");
		break;
	case DEFAULT:
		ActionToButtonMap[action]->setStyleSheet("background-color:auto;");
		break;

	}
}

void OptionsDialog::resetAllColor()
{
	QMapIterator<Action,QPushButton*> i(ActionToButtonMap);
	 while (i.hasNext()) {
		 i.next();
		 setButtonColor(DEFAULT,(Action)i.key());
	 }
}

void OptionsDialog::configureMap()
{
	ActionToButtonMap[UP]=ui->buttonUp;
	ActionToButtonMap[DOWN]=ui->buttonDown;
	ActionToButtonMap[LEFT]=ui->buttonLeft;
	ActionToButtonMap[RIGHT]=ui->buttonRight;
	ActionToButtonMap[JUMP]=ui->buttonJump;
}
