#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QWidget>
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {

#if 0
struct tag_SBUS_BIT_PICK {
    int8_t chan_index;
    uint16_t mask;
    int8_t rshift;
    int8_t lshift;
};
#endif
//typedef struct tag_SBUS_BIT_PICK SBUS_BIT_PICK;

//struct telephone
//{
//        char *name;
//        int number;
//};

#if 0
static const struct sbus_bit_pick sbus_encoder[23][2] = {
/* 0  */ { { 0, 0x0ff, 0, 0}, { -1, 0, 0, 0} },
/* 1  */ { { 0, 0x700, 8, 0}, { 1, 0x01f, 0, 5} },
/* 2  */ { { 1, 0x7e0, 5, 0}, { 2, 0x003, 0, 6} },
/* 3  */ { { 2, 0x3fc, 2, 0}, { -1, 0, 0, 0} },
/* 4  */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 5  */ { {-1, 0x200, 9, 0}, { -1, 0x07f, 0, 1} },
/* 6  */ { {-1, 0x200, 9, 0}, { -1, 0x07f, 0, 1} },
/* 7  */ { {-1, 0x200, 9, 0}, { -1, 0x07f, 0, 1} },
/* 8  */ { { 2, 0x200, 9, 0}, { -1, 0x07f, 0, 1} },
/* 9  */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 10 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 11 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 12 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 13 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 14 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 15 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 16 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 17 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 18 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 19 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 20 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 21 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} },
/* 22 */ { { 2, 0x200, 9, 0}, { 4, 0x07f, 0, 1} }
};
#endif

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Transmit_clicked(void);
    void on_CenterChannelsPushButton_clicked(void);
    void on_MinimizeChannelsPushButton_clicked(void);
    void on_MaximizeChannelsPushButton_clicked(void);

    void sliderValueChanged_ch1(int val);
    void sliderValueChanged_ch2(int val);
    void sliderValueChanged_ch3(int val);
    void sliderValueChanged_ch4(int val);
    void sliderValueChanged_ch5(int val);
    void sliderValueChanged_ch6(int val);
    void sliderValueChanged_ch7(int val);
    void sliderValueChanged_ch8(int val);
    void sliderValueChanged_ch9(int val);
    void sliderValueChanged_ch10(int val);
    void sliderValueChanged_ch11(int val);
    void sliderValueChanged_ch12(int val);
    void sliderValueChanged_ch13(int val);
    void sliderValueChanged_ch14(int val);
    void sliderValueChanged_ch15(int val);
    void sliderValueChanged_ch16(int val);

    void radioButtonDsmxClicked(void);
    void radioButtonSBusClicked(void);

    void RadioButtonFlightModeStabilize_Clicked();
    void RadioButtonFlightModeAltitudeHold_Clicked();
    void RadioButtonFlightModeLand_Clicked();
    void RadioButtonFlightModeSport_Clicked();


//    void on_radioButton_SBus_clicked(int val);
//    void on_radioButton_DSMX_clicked(int val);


    void on_TimerTick(void);

private:
    Ui::MainWindow *ui;

    QSerialPort *m_pSerialPort;
    QTimer      *m_pStepTimer;

    bool        _bTransmitOn;
    long        _lFramesTransmitted;

    bool        _bSBus;

    uint16_t    _u16_ChanVal[16];

    // S-Bus data
    uint32_t    SBUS_Channel_Data[18];
    uint8_t     SBUS_Current_Channel = 0;
    uint8_t     SBUS_Current_Channel_Bit = 0;
    uint8_t     SBUS_Current_Packet_Bit = 0;
    uint8_t     SBUS_Packet_Data[25];
    uint8_t     SBUS_Packet_Position = 0;

    uint16_t    QSMX_Channel_Data[12];
    uint8_t     QSMX_Packet_Data[16];
    uint8_t     QSMX_Packet_Position = 0;

    uint8_t     SBUS_Failsafe_Active = 0;
    uint8_t     SBUS_Lost_Frame = 0;

//    SBUS_BIT_PICK sbus_encoder;

  //  struct telephone my_index;

  //  [2] = {
  //  /* 0  */ { { 0, 0x0ff, 0, 0}, { -1, 0, 0, 0} },
  //  /* 1  */ { { 0, 0x700, 8, 0}, { 1, 0x01f, 0, 5} },
  //  /* 2  */ { { 1, 0x7e0, 5, 0}, { 2, 0x003, 0, 6} },



private:
    void SBUS_SetupPacket(void);
    void QSMX_SetupPacket(void);
//    int set_interface_attribs (int fd, int speed, int parity);
//    void set_blocking (int fd, int should_block);
    void SBUS_BuildPacket(void);
    void QSMX_BuildPacket(void);

};

#endif // MAINWINDOW_H
