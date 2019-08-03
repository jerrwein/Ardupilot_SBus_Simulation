#include "mainwindow.h"
#include "ui_mainwindow.h"

#define SBUS_FAILSAFE_BIT	3
#define SBUS_FRAMELOST_BIT	2
#define SBUS_SERVO_BIT_1    1
#define SBUS_SERVO_BIT_2    0

#define FLIGHT_MODE_LAND 390
#define FLIGHT_MODE_STABILIZE 675
#define FLIGHT_MODE_ALTHOLD 898
#define FLIGHT_MODE_SPORT 1120
#define FLIGHT_MODE_TBD1 1339
#define FLIGHT_MODE_TBD2 1700



struct tag_SBUS_BIT_PICK {
    int8_t chan_index;
    uint16_t mask;
    int8_t rshift;
    int8_t lshift;
};

//struct tag_SBUS_BIT_PICK sbus_encoder1;
//const struct tag_SBUS_BIT_PICK sbus_encoder2 = { 0, 0x0ff, 0, 0 };
//const struct tag_SBUS_BIT_PICK sbus_encoder3[2] = { { 0, 0x0ff, 0, 0 }, { 0, 0x0ff, 0, 0 } };
//const struct tag_SBUS_BIT_PICK sbus_encoder4[][2] = { { { 0, 0x0ff, 0, 0 }, { 0, 0x0ff, 0, 0 } },
 //                                                     { { 0, 0x0ff, 0, 0 }, { 0, 0x0ff, 0, 0 } } };

//static struct SBUS_BIT_PICK sbus_encoder;

#if 1
const struct tag_SBUS_BIT_PICK sbus_encoder[][2] = {
/* 0  */ { {  0, 0x0ff,  0, 0}, { -1,     0, 0, 0} },
/* 1  */ { {  0, 0x700,  8, 0}, {  1, 0x01f, 0, 3} },
/* 2  */ { {  1, 0x7e0,  5, 0}, {  2, 0x003, 0, 6} },
/* 3  */ { {  2, 0x3fc,  2, 0}, { -1,     0, 0, 0} },
/* 4  */ { {  2, 0x400, 10, 0}, {  3, 0x07f, 0, 1} },
/* 5  */ { {  3, 0x780,  7, 0}, {  4, 0x00f, 0, 4} },
/* 6  */ { {  4, 0x7f0,  4, 0}, {  5, 0x001, 0, 7} },
/* 7  */ { {  5, 0x1fe,  1, 0}, { -1,     0, 0, 0} },
/* 8  */ { {  5, 0x600,  9, 0}, {  6, 0x03f, 0, 2} },
/* 9  */ { {  6, 0x7c0,  6, 0}, {  7, 0x007, 0, 5} },
/* 10 */ { {  7, 0x7f8,  3, 0}, { -1,     0, 0, 0} },
/* 11 */ { {  8, 0x0ff,  0, 0}, { -1,     0, 0, 1} },
/* 12 */ { {  8, 0x700,  8, 0}, {  9, 0x01f, 0, 3} },
/* 13 */ { {  9, 0x7e0,  5, 0}, { 10, 0x003, 0, 6} },
/* 14 */ { { 10, 0x3fc,  2, 0}, { -1,     0, 0, 0} },
/* 15 */ { { 10, 0x400, 10, 0}, { 11, 0x07f, 0, 1} },
/* 16 */ { { 11, 0x780,  7, 0}, { 12, 0x00f, 0, 4} },
/* 17 */ { { 12, 0x7f0,  4, 0}, { 13, 0x001, 0, 7} },
/* 18 */ { { 13, 0x1fe,  1, 0}, { -1,     0, 0, 0} },
/* 19 */ { { 13, 0x600,  9, 0}, { 14, 0x03f, 0, 2} },
/* 20 */ { { 14, 0x7c0,  6, 0}, { 15, 0x007, 0, 5} },
/* 21 */ { { 15, 0x7f8,  3, 0}, { -1,     0, 0, 0} }
};
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _u16_ChanVal[0] = 1500;
    _u16_ChanVal[1] = 1500;
    _u16_ChanVal[2] = 1500;
    _u16_ChanVal[3] = 1500;
    _u16_ChanVal[4] = FLIGHT_MODE_STABILIZE;
    _u16_ChanVal[5] = 902;
    _u16_ChanVal[6] = 903;
    _u16_ChanVal[7] = 904;
    _u16_ChanVal[8] = 905;
    _u16_ChanVal[9] = 906;
    _u16_ChanVal[10] = 907;
    _u16_ChanVal[11] = 908;
    _u16_ChanVal[12] = 909;
    _u16_ChanVal[13] = 910;
    _u16_ChanVal[14] = 911;
    _u16_ChanVal[15] = 912;

    ui->checkBox_DigServo1->setChecked(false);
    ui->checkBox_DigServo1->setChecked(true);
    ui->checkBox_DroppedFrame->setChecked(false);
    ui->checkBox_FailSafe->setChecked(false);

    ui->lineEdit_ch1->setText(QString::number(_u16_ChanVal[0], 10));
    ui->lineEdit_ch2->setText(QString::number(_u16_ChanVal[1], 10));
    ui->lineEdit_ch3->setText(QString::number(_u16_ChanVal[2], 10));
    ui->lineEdit_ch4->setText(QString::number(_u16_ChanVal[3], 10));
    ui->lineEdit_ch5->setText(QString::number(_u16_ChanVal[4], 10));
    ui->lineEdit_ch6->setText(QString::number(_u16_ChanVal[5], 10));
    ui->lineEdit_ch7->setText(QString::number(_u16_ChanVal[6], 10));
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[7], 10));
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[8], 10));
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[9], 10));
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[10], 10));
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[11], 10));
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[12], 10));
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[13], 10));
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[14], 10));
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[15], 10));

    ui->verticalSlider_ch1->setRange(344, 1705);
    ui->verticalSlider_ch2->setRange(344, 1705);
    ui->verticalSlider_ch3->setRange(344, 1705);
    ui->verticalSlider_ch4->setRange(344, 1705);
    ui->verticalSlider_ch5->setRange(344, 1705);
    ui->verticalSlider_ch6->setRange(344, 1705);
    ui->verticalSlider_ch7->setRange(344, 1705);
    ui->verticalSlider_ch8->setRange(344, 1705);
    ui->verticalSlider_ch9->setRange(1100, 1900);
    ui->verticalSlider_ch10->setRange(1100, 1900);
    ui->verticalSlider_ch11->setRange(1100, 1900);
    ui->verticalSlider_ch12->setRange(1100, 1900);
    ui->verticalSlider_ch13->setRange(200, 1800);
    ui->verticalSlider_ch14->setRange(200, 1800);
    ui->verticalSlider_ch15->setRange(200, 1800);
    ui->verticalSlider_ch16->setRange(200, 1800);

    ui->verticalSlider_ch8->setEnabled(false);
    ui->verticalSlider_ch9->setEnabled(false);
    ui->verticalSlider_ch10->setEnabled(false);
    ui->verticalSlider_ch11->setEnabled(false);
    ui->verticalSlider_ch12->setEnabled(false);
    ui->verticalSlider_ch13->setEnabled(false);
    ui->verticalSlider_ch14->setEnabled(false);
    ui->verticalSlider_ch15->setEnabled(false);
    ui->verticalSlider_ch16->setEnabled(false);

    ui->verticalSlider_ch1->setValue(_u16_ChanVal[0]);
    ui->verticalSlider_ch2->setValue(_u16_ChanVal[1]);
    ui->verticalSlider_ch3->setValue(_u16_ChanVal[2]);
    ui->verticalSlider_ch4->setValue(_u16_ChanVal[3]);
    ui->verticalSlider_ch5->setValue(_u16_ChanVal[4]);
    ui->verticalSlider_ch6->setValue(_u16_ChanVal[5]);
    ui->verticalSlider_ch7->setValue(_u16_ChanVal[6]);
    ui->verticalSlider_ch8->setValue(_u16_ChanVal[7]);
    ui->verticalSlider_ch9->setValue(_u16_ChanVal[8]);
    ui->verticalSlider_ch10->setValue(_u16_ChanVal[9]);
    ui->verticalSlider_ch11->setValue(_u16_ChanVal[10]);
    ui->verticalSlider_ch12->setValue(_u16_ChanVal[11]);
    ui->verticalSlider_ch13->setValue(_u16_ChanVal[12]);
    ui->verticalSlider_ch14->setValue(_u16_ChanVal[13]);
    ui->verticalSlider_ch15->setValue(_u16_ChanVal[14]);
    ui->verticalSlider_ch16->setValue(_u16_ChanVal[15]);

    connect(ui->verticalSlider_ch1,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch1(int)));
    connect(ui->verticalSlider_ch2,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch2(int)));
    connect(ui->verticalSlider_ch3,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch3(int)));
    connect(ui->verticalSlider_ch4,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch4(int)));
    connect(ui->verticalSlider_ch5,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch5(int)));
    connect(ui->verticalSlider_ch6,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch6(int)));
    connect(ui->verticalSlider_ch7,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch7(int)));
    connect(ui->verticalSlider_ch8,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch8(int)));
    connect(ui->verticalSlider_ch9,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch9(int)));
    connect(ui->verticalSlider_ch10,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch10(int)));
    connect(ui->verticalSlider_ch11,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch11(int)));
    connect(ui->verticalSlider_ch12,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch12(int)));
    connect(ui->verticalSlider_ch13,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch13(int)));
    connect(ui->verticalSlider_ch14,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch14(int)));
    connect(ui->verticalSlider_ch15,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch15(int)));
    connect(ui->verticalSlider_ch16,SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged_ch16(int)));

    connect(ui->radioButton_DSMX,SIGNAL(clicked()),this,SLOT(radioButtonDsmxClicked()));
    connect(ui->radioButton_SBus,SIGNAL(clicked()),this,SLOT(radioButtonSBusClicked()));

    connect(ui->radioButton_FlightMode_Stabilize,SIGNAL(clicked()),this,SLOT(RadioButtonFlightModeStabilize_Clicked()));
    connect(ui->radioButton_FlightMode_AltHold,SIGNAL(clicked()),this,SLOT(RadioButtonFlightModeAltitudeHold_Clicked()));
    connect(ui->radioButton_FlightMode_Land,SIGNAL(clicked()),this,SLOT(RadioButtonFlightModeLand_Clicked()));
    connect(ui->radioButton_FlightMode_Sport,SIGNAL(clicked()),this,SLOT(RadioButtonFlightModeSport_Clicked()));


    void RadioButtonFlightModeLand_Clicked();
    void RadioButtonFlightModeSport_Clicked();


    m_pSerialPort = NULL;
    m_pSerialPort = new QSerialPort("/dev/ttyS4");
    if (m_pSerialPort->open(QIODevice::ReadWrite))
    {
        qDebug() << "Baud rate:" << m_pSerialPort->baudRate();
        qDebug() << "Data bits:" << m_pSerialPort->dataBits();
        qDebug() << "Stop bits:" << m_pSerialPort->stopBits();
        qDebug() << "Parity:" << m_pSerialPort->parity();
        qDebug() << "Flow control:" << m_pSerialPort->flowControl();
        qDebug() << "Read buffer size:" << m_pSerialPort->readBufferSize();
    }

    if (ui->radioButton_SBus->isChecked())
    {
        m_pSerialPort->setBaudRate(19200);
        m_pSerialPort->setDataBits(m_pSerialPort->Data8);
        m_pSerialPort->setStopBits(m_pSerialPort->TwoStop);
        m_pSerialPort->setParity(m_pSerialPort->EvenParity);
    }
    else
    {   // This for Spectrum simulation.
//      m_pSerialPort->setBaudRate(19200);
//        m_pSerialPort->setBaudRate(57600);
        m_pSerialPort->setBaudRate(115200);
        m_pSerialPort->setDataBits(m_pSerialPort->Data8);
        m_pSerialPort->setStopBits(m_pSerialPort->OneStop);
        m_pSerialPort->setParity(m_pSerialPort->NoParity);
    }

    /*
     * In normal operation, the Spektrum remotes issue a 16
     * byte data packet every 11ms or 22ms, depending
     * upon the selected protocol. The packet is transmitted
     * at 125000bps, 8 bits, No parity, 1 stop (8N1)
     */

     _bTransmitOn = false;
    _lFramesTransmitted = 0;

    // Timer
    m_pStepTimer = new QTimer(this);
    m_pStepTimer->stop();
    connect(m_pStepTimer, SIGNAL(timeout()), this, SLOT(on_TimerTick()));
//    timer->start(1000);
}

MainWindow::~MainWindow()
{
    if (NULL != m_pSerialPort)
    {
        m_pSerialPort->close();
        delete m_pSerialPort;
    }
    if(m_pStepTimer)
    {
        m_pStepTimer->stop();
        delete m_pStepTimer;
    }

    delete ui;
}


void MainWindow::RadioButtonFlightModeStabilize_Clicked(void)
{
    _u16_ChanVal[4] = FLIGHT_MODE_STABILIZE;
    ui->verticalSlider_ch5->setValue(_u16_ChanVal[4]);
}

void MainWindow::RadioButtonFlightModeAltitudeHold_Clicked(void)
{
    _u16_ChanVal[4] = FLIGHT_MODE_ALTHOLD;
    ui->verticalSlider_ch5->setValue(_u16_ChanVal[4]);
}

void MainWindow::RadioButtonFlightModeLand_Clicked(void)
{
    _u16_ChanVal[4] = FLIGHT_MODE_LAND;
    ui->verticalSlider_ch5->setValue(_u16_ChanVal[4]);
}

void MainWindow::RadioButtonFlightModeSport_Clicked(void)
{
    _u16_ChanVal[4] = FLIGHT_MODE_SPORT;
    ui->verticalSlider_ch5->setValue(_u16_ChanVal[4]);
}

void MainWindow::radioButtonSBusClicked(void)
{
    ui->verticalSlider_ch1->setRange(200, 1800);
    ui->verticalSlider_ch2->setRange(200, 1800);
    ui->verticalSlider_ch3->setRange(200, 1800);
    ui->verticalSlider_ch4->setRange(200, 1800);
    ui->verticalSlider_ch5->setRange(200, 1800);
    ui->verticalSlider_ch6->setRange(200, 1800);
    ui->verticalSlider_ch7->setRange(200, 1800);
    ui->verticalSlider_ch8->setRange(200, 1800);

    ui->verticalSlider_ch8->setEnabled(true);
    ui->verticalSlider_ch9->setEnabled(true);
    ui->verticalSlider_ch10->setEnabled(true);
    ui->verticalSlider_ch11->setEnabled(true);
    ui->verticalSlider_ch12->setEnabled(true);
    ui->verticalSlider_ch13->setEnabled(true);
    ui->verticalSlider_ch14->setEnabled(true);
    ui->verticalSlider_ch15->setEnabled(true);
    ui->verticalSlider_ch16->setEnabled(true);
}

void MainWindow::radioButtonDsmxClicked(void)
{

    ui->verticalSlider_ch1->setRange(1100, 1900);
    ui->verticalSlider_ch2->setRange(1100, 1900);
    ui->verticalSlider_ch3->setRange(172, 1876);
    ui->verticalSlider_ch4->setRange(172, 1876);
    ui->verticalSlider_ch5->setRange(172, 1876);
    ui->verticalSlider_ch6->setRange(172, 1876);
    ui->verticalSlider_ch7->setRange(172, 1876);
//    ui->verticalSlider_ch8->setRange(172, 1876);

    ui->verticalSlider_ch8->setEnabled(false);
    ui->verticalSlider_ch9->setEnabled(false);
    ui->verticalSlider_ch10->setEnabled(false);
    ui->verticalSlider_ch11->setEnabled(false);
    ui->verticalSlider_ch12->setEnabled(false);
    ui->verticalSlider_ch13->setEnabled(false);
    ui->verticalSlider_ch14->setEnabled(false);
    ui->verticalSlider_ch15->setEnabled(false);
    ui->verticalSlider_ch16->setEnabled(false);
}

void MainWindow::on_pushButton_Transmit_clicked(void)
{
    if (!_bTransmitOn)
    {
        if (ui->radioButton_SBus->isChecked())
            _bSBus = true;
        else
            _bSBus = false;
        _bTransmitOn = true;
        m_pStepTimer->start(15);
        ui->pushButton_Transmit->setText("Stop Transmit");
    }
    else
    {
         _bTransmitOn = false;
         m_pStepTimer->stop();
         ui->pushButton_Transmit->setText("Start Transmit");
    }
}

void MainWindow::on_CenterChannelsPushButton_clicked(void)
{
    if (ui->verticalSlider_ch1->isEnabled())
        _u16_ChanVal[0] = 1000;
    if (ui->verticalSlider_ch2->isEnabled())
        _u16_ChanVal[1] = 1000;
    if (ui->verticalSlider_ch3->isEnabled())
        _u16_ChanVal[2] = 1000;
    if (ui->verticalSlider_ch4->isEnabled())
        _u16_ChanVal[3] = 1000;
    if (ui->verticalSlider_ch5->isEnabled())
        _u16_ChanVal[4] = 1000;
    if (ui->verticalSlider_ch6->isEnabled())
        _u16_ChanVal[5] = 1000;
    if (ui->verticalSlider_ch7->isEnabled())
        _u16_ChanVal[6] = 1000;
    if (ui->verticalSlider_ch8->isEnabled())
        _u16_ChanVal[7] = 1000;
    if (ui->verticalSlider_ch9->isEnabled())
        _u16_ChanVal[8] = 1000;
    if (ui->verticalSlider_ch10->isEnabled())
        _u16_ChanVal[9] = 1000;
    if (ui->verticalSlider_ch11->isEnabled())
        _u16_ChanVal[10] = 1000;
    if (ui->verticalSlider_ch12->isEnabled())
        _u16_ChanVal[11] = 1000;
    if (ui->verticalSlider_ch13->isEnabled())
        _u16_ChanVal[12] = 1000;
    if (ui->verticalSlider_ch14->isEnabled())
        _u16_ChanVal[13] = 1000;
    if (ui->verticalSlider_ch15->isEnabled())
        _u16_ChanVal[14] = 1000;
    if (ui->verticalSlider_ch16->isEnabled())
        _u16_ChanVal[15] = 1000;

    ui->lineEdit_ch1->setText(QString::number(_u16_ChanVal[0], 10));
    ui->lineEdit_ch2->setText(QString::number(_u16_ChanVal[1], 10));
    ui->lineEdit_ch3->setText(QString::number(_u16_ChanVal[2], 10));
    ui->lineEdit_ch4->setText(QString::number(_u16_ChanVal[3], 10));
    ui->lineEdit_ch5->setText(QString::number(_u16_ChanVal[4], 10));
    ui->lineEdit_ch6->setText(QString::number(_u16_ChanVal[5], 10));
    ui->lineEdit_ch7->setText(QString::number(_u16_ChanVal[6], 10));
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[7], 10));
    ui->lineEdit_ch9->setText(QString::number(_u16_ChanVal[8], 10));
    ui->lineEdit_ch10->setText(QString::number(_u16_ChanVal[9], 10));
    ui->lineEdit_ch11->setText(QString::number(_u16_ChanVal[10], 10));
    ui->lineEdit_ch12->setText(QString::number(_u16_ChanVal[11], 10));
    ui->lineEdit_ch13->setText(QString::number(_u16_ChanVal[12], 10));
    ui->lineEdit_ch14->setText(QString::number(_u16_ChanVal[13], 10));
    ui->lineEdit_ch15->setText(QString::number(_u16_ChanVal[14], 10));
    ui->lineEdit_ch16->setText(QString::number(_u16_ChanVal[15], 10));

    ui->verticalSlider_ch1->setValue(_u16_ChanVal[0]);
    ui->verticalSlider_ch2->setValue(_u16_ChanVal[1]);
    ui->verticalSlider_ch3->setValue(_u16_ChanVal[2]);
    ui->verticalSlider_ch4->setValue(_u16_ChanVal[3]);
    ui->verticalSlider_ch5->setValue(_u16_ChanVal[4]);
    ui->verticalSlider_ch6->setValue(_u16_ChanVal[5]);
    ui->verticalSlider_ch7->setValue(_u16_ChanVal[6]);
    ui->verticalSlider_ch8->setValue(_u16_ChanVal[7]);
    ui->verticalSlider_ch9->setValue(_u16_ChanVal[8]);
    ui->verticalSlider_ch10->setValue(_u16_ChanVal[9]);
    ui->verticalSlider_ch11->setValue(_u16_ChanVal[10]);
    ui->verticalSlider_ch12->setValue(_u16_ChanVal[11]);
    ui->verticalSlider_ch13->setValue(_u16_ChanVal[12]);
    ui->verticalSlider_ch14->setValue(_u16_ChanVal[13]);
    ui->verticalSlider_ch15->setValue(_u16_ChanVal[14]);
    ui->verticalSlider_ch16->setValue(_u16_ChanVal[15]);
}

void MainWindow::on_MinimizeChannelsPushButton_clicked(void)
{
    if (ui->verticalSlider_ch1->isEnabled())
        _u16_ChanVal[0] = 344;
    if (ui->verticalSlider_ch2->isEnabled())
        _u16_ChanVal[1] = 344;
    if (ui->verticalSlider_ch3->isEnabled())
        _u16_ChanVal[2] = 344;
    if (ui->verticalSlider_ch4->isEnabled())
        _u16_ChanVal[3] = 344;
    if (ui->verticalSlider_ch5->isEnabled())
        _u16_ChanVal[4] = 344;
    if (ui->verticalSlider_ch6->isEnabled())
        _u16_ChanVal[5] = 344;
    if (ui->verticalSlider_ch7->isEnabled())
        _u16_ChanVal[6] = 344;
    if (ui->verticalSlider_ch8->isEnabled())
        _u16_ChanVal[7] = 344;

    ui->lineEdit_ch1->setText(QString::number(_u16_ChanVal[0], 10));
    ui->lineEdit_ch2->setText(QString::number(_u16_ChanVal[1], 10));
    ui->lineEdit_ch3->setText(QString::number(_u16_ChanVal[2], 10));
    ui->lineEdit_ch4->setText(QString::number(_u16_ChanVal[3], 10));
    ui->lineEdit_ch5->setText(QString::number(_u16_ChanVal[4], 10));
    ui->lineEdit_ch6->setText(QString::number(_u16_ChanVal[5], 10));
    ui->lineEdit_ch7->setText(QString::number(_u16_ChanVal[6], 10));
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[7], 10));

    ui->verticalSlider_ch1->setValue(_u16_ChanVal[0]);
    ui->verticalSlider_ch2->setValue(_u16_ChanVal[1]);
    ui->verticalSlider_ch3->setValue(_u16_ChanVal[2]);
    ui->verticalSlider_ch4->setValue(_u16_ChanVal[3]);
    ui->verticalSlider_ch5->setValue(_u16_ChanVal[4]);
    ui->verticalSlider_ch6->setValue(_u16_ChanVal[5]);
    ui->verticalSlider_ch7->setValue(_u16_ChanVal[6]);
    ui->verticalSlider_ch8->setValue(_u16_ChanVal[7]);
}

void MainWindow::on_MaximizeChannelsPushButton_clicked(void)
{
    if (ui->verticalSlider_ch1->isEnabled())
        _u16_ChanVal[0] = 1705;
    if (ui->verticalSlider_ch2->isEnabled())
        _u16_ChanVal[1] = 1705;
    if (ui->verticalSlider_ch3->isEnabled())
        _u16_ChanVal[2] = 1705;
    if (ui->verticalSlider_ch4->isEnabled())
        _u16_ChanVal[3] = 1705;
    if (ui->verticalSlider_ch5->isEnabled())
        _u16_ChanVal[4] = 1705;
    if (ui->verticalSlider_ch6->isEnabled())
        _u16_ChanVal[5] = 1705;
    if (ui->verticalSlider_ch7->isEnabled())
        _u16_ChanVal[6] = 1705;
    if (ui->verticalSlider_ch8->isEnabled())
        _u16_ChanVal[7] = 1705;

    ui->lineEdit_ch1->setText(QString::number(_u16_ChanVal[0], 10));
    ui->lineEdit_ch2->setText(QString::number(_u16_ChanVal[1], 10));
    ui->lineEdit_ch3->setText(QString::number(_u16_ChanVal[2], 10));
    ui->lineEdit_ch4->setText(QString::number(_u16_ChanVal[3], 10));
    ui->lineEdit_ch5->setText(QString::number(_u16_ChanVal[4], 10));
    ui->lineEdit_ch6->setText(QString::number(_u16_ChanVal[5], 10));
    ui->lineEdit_ch7->setText(QString::number(_u16_ChanVal[6], 10));
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[7], 10));

    ui->verticalSlider_ch1->setValue(_u16_ChanVal[0]);
    ui->verticalSlider_ch2->setValue(_u16_ChanVal[1]);
    ui->verticalSlider_ch3->setValue(_u16_ChanVal[2]);
    ui->verticalSlider_ch4->setValue(_u16_ChanVal[3]);
    ui->verticalSlider_ch5->setValue(_u16_ChanVal[4]);
    ui->verticalSlider_ch6->setValue(_u16_ChanVal[5]);
    ui->verticalSlider_ch7->setValue(_u16_ChanVal[6]);
    ui->verticalSlider_ch8->setValue(_u16_ChanVal[7]);
}


void MainWindow::on_TimerTick(void)
{
    if (_bTransmitOn)
    {
        if (_bSBus)
        {
            SBUS_SetupPacket();
            SBUS_BuildPacket();
            m_pSerialPort->write((const char *)SBUS_Packet_Data, 25);
        }
        else
        {
            QSMX_SetupPacket();
            QSMX_BuildPacket();
            m_pSerialPort->write((const char *)QSMX_Packet_Data, 16);
        }
        _lFramesTransmitted++;

        qDebug() << "TimerTick() Transmitted frames" << QString::number(_lFramesTransmitted, 10);
    }
    //qDebug() << "Get NumElemsMoveFifo suceeded:" << QString::number(tVarInfo.U16_Val, 10);

}

void MainWindow::SBUS_SetupPacket(void)
{
  //  SBUS_Channel_Data[0] = 210;
    SBUS_Channel_Data[0] = _u16_ChanVal[0];
 //   SBUS_Channel_Data[1] = 220;
    SBUS_Channel_Data[1] = _u16_ChanVal[1];
 //   SBUS_Channel_Data[2] = 300;
    SBUS_Channel_Data[2] = _u16_ChanVal[2];
    SBUS_Channel_Data[3] = _u16_ChanVal[3];
    SBUS_Channel_Data[4] = _u16_ChanVal[4];
    SBUS_Channel_Data[5] = _u16_ChanVal[5];
    SBUS_Channel_Data[6] = _u16_ChanVal[6];
    SBUS_Channel_Data[7] = _u16_ChanVal[7];
    SBUS_Channel_Data[8] = _u16_ChanVal[8];
    SBUS_Channel_Data[9] = _u16_ChanVal[9];
    SBUS_Channel_Data[10] = _u16_ChanVal[10];
    SBUS_Channel_Data[11] = _u16_ChanVal[11];
    SBUS_Channel_Data[12] = _u16_ChanVal[12];
    SBUS_Channel_Data[13] = _u16_ChanVal[13];
    SBUS_Channel_Data[14] = _u16_ChanVal[14];
    SBUS_Channel_Data[15] = _u16_ChanVal[15];
    SBUS_Channel_Data[16] = 0;  // Servo bit
    SBUS_Channel_Data[17] = 0;  // Servo bit
    SBUS_Failsafe_Active = 0;
    SBUS_Lost_Frame = 0;
}

void MainWindow::QSMX_SetupPacket(void)
{
    QSMX_Channel_Data[0] = _u16_ChanVal[0];
    QSMX_Channel_Data[1] = _u16_ChanVal[1];
    QSMX_Channel_Data[2] = _u16_ChanVal[2];
    QSMX_Channel_Data[3] = _u16_ChanVal[3];
    QSMX_Channel_Data[4] = _u16_ChanVal[4];
    QSMX_Channel_Data[5] = _u16_ChanVal[5];
    QSMX_Channel_Data[6] = _u16_ChanVal[6];
    QSMX_Channel_Data[7] = _u16_ChanVal[7];
    QSMX_Channel_Data[8] = _u16_ChanVal[8];
    QSMX_Channel_Data[9] = _u16_ChanVal[9];
    QSMX_Channel_Data[10] = _u16_ChanVal[10];
    QSMX_Channel_Data[11] = _u16_ChanVal[11];
//    QSMX_Channel_Data[12] = _u16_ChanVal[12];
//  SBUS_Failsafe_Active = 0;
//  SBUS_Lost_Frame = 0;
}

#if 0
void MainWindow::SBUS_BuildPacket(void)
{
    // Zero out packet data
    for(SBUS_Packet_Position=0; SBUS_Packet_Position<25; SBUS_Packet_Position++)
        SBUS_Packet_Data[SBUS_Packet_Position] = 0x00;

//    SBUS_Current_Packet_Bit = 0;
    SBUS_Current_Packet_Bit = 7;
    SBUS_Packet_Position = 0;
    SBUS_Packet_Data[SBUS_Packet_Position] = 0x0F;  // Start Byte
    SBUS_Packet_Position++;

    for(SBUS_Current_Channel=0; SBUS_Current_Channel<16; SBUS_Current_Channel++)
    {
        for(SBUS_Current_Channel_Bit=0; SBUS_Current_Channel_Bit<12; SBUS_Current_Channel_Bit++)
        {
      //      if(SBUS_Current_Packet_Bit > 7)
      //      {
      //          SBUS_Current_Packet_Bit = 0;  // If we just set bit 7 in a previous step, reset the packet bit to 0 and
      //          SBUS_Packet_Position++;       // Move to the next packet byte
      //      }
            // Downshift the channel data bit, then upshift it to set the packet data byte
            SBUS_Packet_Data[SBUS_Packet_Position] |= (((SBUS_Channel_Data[SBUS_Current_Channel]>>SBUS_Current_Channel_Bit) & 0x01)<<SBUS_Current_Packet_Bit);
            //SBUS_Current_Packet_Bit++;
             SBUS_Current_Packet_Bit--;

            if(SBUS_Current_Packet_Bit < 0)
            {
                SBUS_Current_Packet_Bit = 7;  // If we just set bit 7 in a previous step, reset the packet bit to 0 and
                SBUS_Packet_Position++;       // Move to the next packet byte
            }
        }
    }
    if (SBUS_Channel_Data[16] > 1023)
        SBUS_Packet_Data[23] |= (1<<SBUS_SERVO_BIT_2);  	// Any number above 1023 will set the digital servo bit
    if (SBUS_Channel_Data[17] > 1023)
        SBUS_Packet_Data[23] |= (1<<SBUS_SERVO_BIT_1);
    if (SBUS_Lost_Frame != 0)
        SBUS_Packet_Data[23] |= (1<<SBUS_FRAMELOST_BIT);		// Any number above 0 will set the lost frame and failsafe bits
    if (SBUS_Failsafe_Active != 0)
        SBUS_Packet_Data[23] |= (1<<SBUS_FAILSAFE_BIT);
    SBUS_Packet_Data[24] = 0x00;			// End byte

 //   int n;
  //  for (n=0; n<25; n++)
  //  {
  //      qDebug() << "Data[" << n << "]: " << QString::number(SBUS_Packet_Data[n], 16);
 //   }

 //   int k;
  //  k = 5;

}
#endif

void MainWindow::SBUS_BuildPacket(void)
{
    // Zero out packet data
    for (SBUS_Packet_Position=0; SBUS_Packet_Position<25; SBUS_Packet_Position++)
        SBUS_Packet_Data[SBUS_Packet_Position] = 0x00;

    // Start byte
    SBUS_Packet_Data[0] = 0x0F;
    SBUS_Packet_Position = 1;
    int chan_index;
    uint8_t lShift, rShift;

    uint16_t u16_data, u16_mask;
    int nPacketIndex;
    for (nPacketIndex=0; nPacketIndex<22; nPacketIndex++)
    {
        chan_index = sbus_encoder[nPacketIndex][0].chan_index;
        u16_mask = sbus_encoder[nPacketIndex][0].mask;
     // lShift = bus_sbus_encoder[nPacketIndex][0].lshift;
        rShift = sbus_encoder[nPacketIndex][0].rshift;

        u16_data = SBUS_Channel_Data[chan_index];
        u16_data = u16_data & u16_mask;
        u16_data = (u16_data >> rShift);
        SBUS_Packet_Data[nPacketIndex+1] |= (uint8_t)u16_data;

        chan_index = sbus_encoder[nPacketIndex][1].chan_index;
        if (0 < chan_index)
        {
            u16_mask = sbus_encoder[nPacketIndex][1].mask;
            lShift = sbus_encoder[nPacketIndex][1].lshift;
        //  rShift = sbus_encoder[nPacketIndex][0].rshift;

            u16_data = SBUS_Channel_Data[chan_index];
            u16_data = u16_data & u16_mask;
            u16_data = (u16_data << lShift);
            SBUS_Packet_Data[nPacketIndex+1] |= (uint8_t)u16_data;
        }
    }
#if 0
    if (SBUS_Channel_Data[16] > 1023)
        SBUS_Packet_Data[23] |= (1<<SBUS_SERVO_BIT_2);  	// Any number above 1023 will set the digital servo bit
    if (SBUS_Channel_Data[17] > 1023)
        SBUS_Packet_Data[23] |= (1<<SBUS_SERVO_BIT_1);
    if (SBUS_Lost_Frame != 0)
        SBUS_Packet_Data[23] |= (1<<SBUS_FRAMELOST_BIT);		// Any number above 0 will set the lost frame and failsafe bits
    if (SBUS_Failsafe_Active != 0)
        SBUS_Packet_Data[23] |= (1<<SBUS_FAILSAFE_BIT);
#endif

    if (ui->checkBox_DigServo1->isChecked())
        SBUS_Packet_Data[23] |= (1<<SBUS_SERVO_BIT_1);

    if (ui->checkBox_DigServo2->isChecked())
        SBUS_Packet_Data[23] |= (1<<SBUS_SERVO_BIT_2);

    if (ui->checkBox_DroppedFrame->isChecked())
        SBUS_Packet_Data[23] |= (1<<SBUS_FRAMELOST_BIT);

    if (ui->checkBox_FailSafe->isChecked())
        SBUS_Packet_Data[23] |= (1<<SBUS_FAILSAFE_BIT);

    // End byte
    SBUS_Packet_Data[24] = 0x00;
}


void MainWindow::QSMX_BuildPacket(void)
{
    // Zero out packet data
    for (QSMX_Packet_Position=0; QSMX_Packet_Position<16; QSMX_Packet_Position++)
        QSMX_Packet_Data[QSMX_Packet_Position] = 0x00;

    /* Message Structure Internal Remote
     * typedef stuct
     * {
     *    UINT8 fades;
     *    UINT8 system;
     *    UINT16 servo[7];
     * } INT_REMOTE_STR;
     *
     * The “system” field will only contain certain values.
     * Any value other than these should be ignored and
     * the unit should behave in a mode appropriate for not having bound.
     *
     * Allowed System Field Values
     * Value Protocol
     * 0x01 22MS 1024 DSM2
     * 0x12 11MS 2048 DSM2
     * 0xa2 22MS 2048 DSMX
     * 0xb2 11MS 2048 DSMX
     *
     * Servo Field 2048 Mode
     * This format is used by all protocols except DSM2/22ms mode.
     * Bits 15 Servo Phase
     * Bits 14-11 Channel ID
     * Bits 10-0 Servo Position
     *
     * Channel Identifiers
     * ID Name
     * 0  Throttle
     * 1  Aileron
     * 2  Elevator
     * 3  Rudder
     * 4  Gear
     * 5  Aux 1
     * 6  Aux 2
     * 7  Aux 3
     * 8  Aux 4
     * 9  Aux 5
     * 10 Aux 6
     * 11 Aux 7
     */

    // 'fades' byte
    QSMX_Packet_Data[0] = 0x00;
    QSMX_Packet_Position = 1;

    // 'system' byte (11ms 2048 DSMX)
    QSMX_Packet_Data[1] = 0xb2;
    QSMX_Packet_Position = 2;

    uint16_t u16_data;

//    float fSlope = 2.048f, fIntercept = -2048.0f, y;
//    float fSlope = 1.28f, fIntercept = -256.0f, y;
    int nPacketIndex;
    // Fourteen bytes available for channel data
    for (nPacketIndex=0; nPacketIndex<7; nPacketIndex++)
    {
        /* Map from [1000-2000] to [0..2047] */
//        y = fSlope*((float)QSMX_Channel_Data[nPacketIndex]) + fIntercept;
//        u16_data = (uint16_t)(y + 0.5);

        u16_data = QSMX_Channel_Data[nPacketIndex];

        /* Pack data int the two assigned bytes */
        QSMX_Packet_Data[QSMX_Packet_Position++] = (uint8_t)((u16_data & 0x700) >> 8);
        QSMX_Packet_Data[QSMX_Packet_Position++] = (uint8_t)(u16_data & 0xff);

        /* Set channel ID - Servo phase=0 */
        QSMX_Packet_Data[QSMX_Packet_Position-2] |= (uint8_t)(nPacketIndex<<3);
    }

 //   QSMX_Packet_Data[4] = 0xde;
 //   QSMX_Packet_Data[5] = 0xad;
 //   QSMX_Packet_Data[6] = 0xbe;
 //   QSMX_Packet_Data[7] = 0xef;

}

void MainWindow::sliderValueChanged_ch1(int val)
{
    _u16_ChanVal[0] = val;
    ui->lineEdit_ch1->setText(QString::number(_u16_ChanVal[0], 10));
}

void MainWindow::sliderValueChanged_ch2(int val)
{
    _u16_ChanVal[1] = val;
    ui->lineEdit_ch2->setText(QString::number(_u16_ChanVal[1], 10));
}

void MainWindow::sliderValueChanged_ch3(int val)
{
    _u16_ChanVal[2] = val;
    ui->lineEdit_ch3->setText(QString::number(_u16_ChanVal[2], 10));
}

void MainWindow::sliderValueChanged_ch4(int val)
{
    _u16_ChanVal[3] = val;
    ui->lineEdit_ch4->setText(QString::number(_u16_ChanVal[3], 10));
}

void MainWindow::sliderValueChanged_ch5(int val)
{
    _u16_ChanVal[4] = val;
    ui->lineEdit_ch5->setText(QString::number(_u16_ChanVal[4], 10));
}

void MainWindow::sliderValueChanged_ch6(int val)
{
    _u16_ChanVal[5] = val;
    ui->lineEdit_ch6->setText(QString::number(_u16_ChanVal[5], 10));
}

void MainWindow::sliderValueChanged_ch7(int val)
{
    _u16_ChanVal[6] = val;
    ui->lineEdit_ch7->setText(QString::number(_u16_ChanVal[6], 10));
}

void MainWindow::sliderValueChanged_ch8(int val)
{
    _u16_ChanVal[7] = val;
    ui->lineEdit_ch8->setText(QString::number(_u16_ChanVal[7], 10));
}

void MainWindow::sliderValueChanged_ch9(int val)
{
    _u16_ChanVal[8] = val;
    ui->lineEdit_ch9->setText(QString::number(_u16_ChanVal[8], 10));
}

void MainWindow::sliderValueChanged_ch10(int val)
{
    _u16_ChanVal[9] = val;
    ui->lineEdit_ch10->setText(QString::number(_u16_ChanVal[9], 10));
}

void MainWindow::sliderValueChanged_ch11(int val)
{
    _u16_ChanVal[10] = val;
    ui->lineEdit_ch11->setText(QString::number(_u16_ChanVal[10], 10));
}

void MainWindow::sliderValueChanged_ch12(int val)
{
    _u16_ChanVal[11] = val;
    ui->lineEdit_ch12->setText(QString::number(_u16_ChanVal[11], 10));
}

void MainWindow::sliderValueChanged_ch13(int val)
{
    _u16_ChanVal[12] = val;
    ui->lineEdit_ch13->setText(QString::number(_u16_ChanVal[12], 10));
}

void MainWindow::sliderValueChanged_ch14(int val)
{
    _u16_ChanVal[13] = val;
    ui->lineEdit_ch14->setText(QString::number(_u16_ChanVal[13], 10));
}

void MainWindow::sliderValueChanged_ch15(int val)
{
    _u16_ChanVal[14] = val;
    ui->lineEdit_ch15->setText(QString::number(_u16_ChanVal[14], 10));
}

void MainWindow::sliderValueChanged_ch16(int val)
{
    _u16_ChanVal[15] = val;
    ui->lineEdit_ch16->setText(QString::number(_u16_ChanVal[15], 10));
}
