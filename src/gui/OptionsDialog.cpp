#include "OptionsDialog.h"
#include "ui_OptionsDialog.h"
#include "../ClientConfiguration.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::OptionsDialog)
{
	ui->setupUi(this);
	load();
	connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onClick(QAbstractButton*)));
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

	if(ui->buttonBox->standardButton(button) == QDialogButtonBox::RestoreDefaults)
	{
		ClientConfiguration config; // Create a default config that will be saved in the default file.
		config.save();
		load(); // Reload the window
	}
}

void OptionsDialog::load()
{
	ClientConfiguration config;
	config.loadDefaultConfigFile();
	ui->seedLineEdit->setText(QVariant(config.getSeed()).toString());
	ui->FPSSpinBox->setValue(config.getFps());
}

void OptionsDialog::save()
{
	ClientConfiguration config;
	config.setSeed(ui->seedLineEdit->text().toInt());
	config.setFps(ui->FPSSpinBox->value());
	config.save();
}
