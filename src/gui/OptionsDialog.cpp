#include "OptionsDialog.h"
#include "ui_OptionsDialog.h"
#include "../ClientConfiguration.h"
#include <QDebug>

OptionsDialog::OptionsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OptionsDialog)
{
	ui->setupUi(this);
	load();

	doubleKey=false;

	connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onClick(QAbstractButton*)));

	/*! IMPOSSIBRUon ne peut pas passer des parametres dans un slot */
	//connect(ui->buttonUp, SIGNAL(clicked()),this,SLOT(changeKey(UP)));

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
		ClientConfiguration config; // Create a default config that will be saved in the default file.
		config.reloadDefault();
		config.save();
		load(); // Reload the window
		checkKey();
	}
}

void OptionsDialog::load()
{
	ClientConfiguration config;
	config.loadDefaultConfigFile();
	ui->seedLineEdit->setText(QVariant(config.getSeed()).toString());
	ui->FPSSpinBox->setValue(config.getFps());
	ui->buttonUp->setText(config.getKeyVal(ClientConfiguration::UP));
	ui->buttonLeft->setText(config.getKeyVal(ClientConfiguration::LEFT));
	ui->buttonDown->setText(config.getKeyVal(ClientConfiguration::DOWN));
	ui->buttonRight->setText(config.getKeyVal(ClientConfiguration::RIGHT));
	ui->buttonJump->setText(config.getKeyVal(ClientConfiguration::JUMP));
	checkKey();
	ui->viewDistanceSpinBox->setValue(config.getViewDistance());
	ui->smoothShadesCheckBox->setChecked(config.getSmoothShades());
	ui->antialiasingCheckBox->setChecked(config.getAntialiasing());
	ui->textureFilteringComboBox->setCurrentIndex(config.getTextureFiltering());
}

void OptionsDialog::save()
{
	ClientConfiguration config;
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
		switch((Action)action)
		{
		case UP:
			ui->buttonUp->setStyleSheet("background-color:#20acd6;");
			break;
		case DOWN:
			ui->buttonDown->setStyleSheet("background-color:#20acd6;");
			break;
		case LEFT:
			ui->buttonLeft->setStyleSheet("background-color:#20acd6;");
			break;
		case RIGHT:
			ui->buttonRight->setStyleSheet("background-color:#20acd6;");
			break;
		case JUMP:
			ui->buttonJump->setStyleSheet("background-color:#20acd6;");
			break;
		}
	}
}

void OptionsDialog::keyPressEvent(QKeyEvent *event)
{
	ClientConfiguration config;
	if(reallocation)
	{
		reallocation=false;
		config.setKey((ClientConfiguration::Action)reallocationKey,event->key());
		switch((Action)reallocationKey)
		{
		case UP:
			ui->buttonUp->setText(config.getKeyVal(ClientConfiguration::UP));
			break;
		case DOWN:
			ui->buttonDown->setText(config.getKeyVal(ClientConfiguration::DOWN));
			break;
		case LEFT:
			ui->buttonLeft->setText(config.getKeyVal(ClientConfiguration::LEFT));
			break;
		case RIGHT:
			ui->buttonRight->setText(config.getKeyVal(ClientConfiguration::RIGHT));
			break;
		case JUMP:
			ui->buttonJump->setText(config.getKeyVal(ClientConfiguration::JUMP));
			break;
		}
	}
	checkKey();
	if(!doubleKey)
	{
		config.save();
		load(); // Reload the window
	}

}

void OptionsDialog::checkKey()
{
	ClientConfiguration config;
	config.loadDefaultConfigFile();
	doubleKey=false;
	QPushButton *okButton=ui->buttonBox->button(QDialogButtonBox::Ok);
	okButton->setEnabled(true);
	ui->buttonUp->setStyleSheet("background-color:auto;");
	ui->buttonDown->setStyleSheet("background-color:auto;");
	ui->buttonLeft->setStyleSheet("background-color:auto;");
	ui->buttonRight->setStyleSheet("background-color:auto;");
	ui->buttonJump->setStyleSheet("background-color:auto;");

	for(int i=0;i<ClientConfiguration::NBVAL;i++)
	{
		int comp = config.getKey((ClientConfiguration::Action)i);
		for(int j=0;j<ClientConfiguration::NBVAL;j++)
		{
			if(comp == config.getKey((ClientConfiguration::Action)j) && i!=j)
			{
				doubleKey=true;
				okButton->setEnabled(false);
				switch((ClientConfiguration::Action)i)
				{
				case UP:
					ui->buttonUp->setStyleSheet("background-color:#ba0000;");
					break;
				case DOWN:
					ui->buttonDown->setStyleSheet("background-color:#ba0000;");
					break;
				case LEFT:
					ui->buttonLeft->setStyleSheet("background-color:#ba0000;");
					break;
				case RIGHT:
					ui->buttonRight->setStyleSheet("background-color:#ba0000;");
					break;
				case JUMP:
					ui->buttonJump->setStyleSheet("background-color:#ba0000;");
					break;
				}
				switch((ClientConfiguration::Action)j)
				{
				case UP:
					ui->buttonUp->setStyleSheet("background-color:#ba0000;");
					break;
				case DOWN:
					ui->buttonDown->setStyleSheet("background-color:#ba0000;");
					break;
				case LEFT:
					ui->buttonLeft->setStyleSheet("background-color:#ba0000;");
					break;
				case RIGHT:
					ui->buttonRight->setStyleSheet("background-color:#ba0000;");
					break;
				case JUMP:
					ui->buttonJump->setStyleSheet("background-color:#ba0000;");
					break;
				}
			}
		}
	}
}
