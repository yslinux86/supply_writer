#include <QDebug>
#include <QMessageBox>
#include <QHostInfo>
#include <QProcess>
#include <QDate>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QRegExpValidator>
#include <QCryptographicHash>
#include <QPainter>

#include "sqlchipinfo.h"
#include "supplywriter.h"
#include "helpdialog.h"

#include "ui_supplywriter.h"

void SupplyWriter::init_market_area()
{
    int kk;

    for (kk = 0; kk < 2; kk++)
    {
        ui->comboBox_3->addItem(_trademark[kk]);
        ui->comboBox_4->addItem(_trademark[kk]);
    }
}

void SupplyWriter::clear_login_page()
{
    ui->username->clear();
    ui->password->clear();
    ui->label_21->clear();

    ui->username->setFocus();
    ui->LoginButton->setDefault(true);
}

void SupplyWriter::clear_main_page()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_14->clear();
    ui->lineEdit_1->clear();

    ui->label_2->clear();
    ui->label_13->clear();
    ui->radioButton_2->setChecked(true);

    ui->label_44->setText(ui->username->text());
    ui->lineEdit_14->setFocus();
    ui->ReadDrumInfo->setEnabled(false);
    ui->ReadTonerInfo->setEnabled(false);
    ui->QuerySqlButton->setEnabled(false);
    ui->DeleteSqlButton->setEnabled(false);

    if (worker == NULL)
        worker = new StateMonitor();

    if (!worker)
        return;

    if (!worker->isRunning())
        worker->start(QThread::NormalPriority);
}

void SupplyWriter::clear_newuser_page()
{
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();

    ui->label_26->clear();

    ui->lineEdit_8->setFocus();
    ui->Confirm->setEnabled(true);
    ui->Return->setEnabled(true);
    ui->Confirm->setDefault(true);
}

void SupplyWriter::clear_renewpwd_page()
{
    ui->lineEdit_15->clear();
    ui->lineEdit_16->clear();
    ui->lineEdit_17->clear();
    ui->lineEdit_18->clear();

    ui->label_31->clear();

    ui->lineEdit_15->setFocus();
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_3->setDefault(true);
}

void SupplyWriter::clear_resetpwd_page0()
{
    ui->lineEdit_19->clear();

    ui->label_41->clear();

    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());

    ui->lineEdit_19->setFocus();
    ui->pushButton_8->setDefault(true);
}

void SupplyWriter::clear_resetpwd_page1()
{
    ui->lineEdit_20->clear();
    ui->lineEdit_21->clear();

    ui->label_40->clear();

    ui->lineEdit_20->setFocus();
    ui->pushButton_9->setEnabled(true);
    ui->pushButton_10->setEnabled(true);
    ui->pushButton_10->setDefault(true);
}

//?????????????????????
void SupplyWriter::login_page_init()
{
    icon.addFile(QString::fromUtf8(":/images/cgprint.png"), QSize(), QIcon::Normal, QIcon::Off);
    this->setWindowIcon(icon);
    setFixedSize(this->width(), this->height());
    this->setWindowFlags(Qt::FramelessWindowHint);
//    current_path = QCoreApplication::applicationDirPath();
//    qDebug() << current_path;
//    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    pixmap[1].load(":/images/title1.png");
    ui->title_label->setScaledContents(false);
    ui->title_label->setPixmap(pixmap[1]);

    pixmap[0].load(":/images/logo.png");
    ui->logo_label->setScaledContents(false);
    ui->logo_label->setPixmap(pixmap[0]);
    ui->label_25->setPixmap(pixmap[0]);

    QFont font1("Microsoft YaHei", 13, 80);
    ui->label_18->setFont(font1);
    QFont font2("Microsoft YaHei", 15, 70);
    ui->label_17->setFont(font2);
    QFont font3("Microsoft YaHei", 11, 65);
    ui->label_20->setFont(font3);

    ui->password->setEchoMode(QLineEdit::Password);
    ui->LoginButton->setDefault(true);
}

//???????????????????????????
void SupplyWriter::main_page_init()
{
    ui->dateEdit->setEnabled(false);

    ui->lineEdit_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_6->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_7->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_11->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_12->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_13->setFocusPolicy(Qt::NoFocus);

    this->init_market_area();
    ui->dateEdit->setDate(QDate::currentDate());

    this->setTabOrder(ui->lineEdit_14, ui->lineEdit);
    this->setTabOrder(ui->lineEdit, ui->lineEdit_4);
    this->setTabOrder(ui->lineEdit_4, ui->lineEdit_5);
    this->setTabOrder(ui->lineEdit_5, ui->lineEdit_1);

    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    db = QSqlDatabase::addDatabase("QODBC", "main");
    player = new QMediaPlayer;

    ui->ReadDrumInfo->setEnabled(false);
    ui->ReadTonerInfo->setEnabled(false);
    ui->QuerySqlButton->setEnabled(false);
    ui->DeleteSqlButton->setEnabled(false);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_connect_fixture()));
    timer->start(3000);
}

//???????????????????????????
void SupplyWriter::newuser_page_init()
{
    pixmap[2].load(":/images/title2.png");
    ui->label_24->setPixmap(pixmap[2]);

    QFont font1("Microsoft YaHei", 15, 70);
    ui->label_22->setFont(font1);
    QFont font2("Microsoft YaHei", 11, 60);
    ui->label_23->setFont(font2);

    ui->lineEdit_9->setEchoMode(QLineEdit::Password);
    ui->lineEdit_10->setEchoMode(QLineEdit::Password);
}

//???????????????????????????
void SupplyWriter::renewpwd_page_init()
{
    pixmap[4].load(":/images/title4.png");
    ui->label_27->setPixmap(pixmap[4]);
    ui->label_28->setPixmap(pixmap[0]);

    QFont font1("Microsoft YaHei", 15, 70);
    ui->label_30->setFont(font1);
    ui->label_39->setFont(font1);
    QFont font2("Microsoft YaHei", 11, 60);
    ui->label_29->setFont(font2);
    ui->label_38->setFont(font2);

    ui->lineEdit_16->setEchoMode(QLineEdit::Password);
    ui->lineEdit_17->setEchoMode(QLineEdit::Password);
    ui->lineEdit_18->setEchoMode(QLineEdit::Password);
}

//???????????????????????????
void SupplyWriter::resetpwd_page_init()
{
    pixmap[3].load(":/images/title3.png");
    ui->label_32->setPixmap(pixmap[3]);

    ui->label_33->setPixmap(pixmap[0]);
    ui->label_43->setPixmap(pixmap[0]);

    QFont font1("Microsoft YaHei", 15, 70);
    ui->label_35->setFont(font1);
    ui->label_39->setFont(font1);
    QFont font2("Microsoft YaHei", 11, 60);
    ui->label_34->setFont(font2);
    ui->label_38->setFont(font2);

    ui->lineEdit_20->setEchoMode(QLineEdit::Password);
    ui->lineEdit_21->setEchoMode(QLineEdit::Password);
}

void SupplyWriter::set_style_sheet(QString filename)
{
    QString qssfile = QString(":/qss/%1").arg(filename);
    QFile skinfile(qssfile);
    skinfile.open(QIODevice::ReadOnly);
    this->setStyleSheet(skinfile.readAll());
    skinfile.close();
}

QImage SupplyWriter::adjust_bright(int bright, const QImage &image)
{
    QImage brightImage(image);
    int r, g, b;

    for (int i = 0; i < image.width(); i++)
    {
        for (int j = 0; j < image.height(); j++)
        {
            QColor oldColor = image.pixelColor(i, j);

            r = qBound(0, oldColor.red() + bright, 255);
            g = qBound(0, oldColor.green() + bright, 255);
            b = qBound(0, oldColor.blue() + bright, 255);

            brightImage.setPixelColor(i, j, QColor(r, g, b));
        }
    }

    return brightImage;
}

SupplyWriter::SupplyWriter(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SupplyWriter)
{
    ui->setupUi(this);

    set_style_sheet("light.qss");

    this->login_page_init();
    this->main_page_init();
    this->newuser_page_init();
    this->renewpwd_page_init();
    this->resetpwd_page_init();
}

// NOT USED
void SupplyWriter::set_dialog_style()
{
    palette.setColor(QPalette::Window, QColor(218, 176, 154));
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::Base, QColor(216, 191, 216));
    palette.setColor(QPalette::AlternateBase, Qt::green);
    palette.setColor(QPalette::ToolTipBase, Qt::darkGray);
    palette.setColor(QPalette::ToolTipText, Qt::black);
    palette.setColor(QPalette::Text, Qt::black);

    palette.setColor(QPalette::Button, Qt::white);
    palette.setColor(QPalette::ButtonText, Qt::black);

    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Highlight, Qt::black);
    palette.setColor(QPalette::HighlightedText, Qt::white);
    this->setPalette(palette);
}
#if 0
void SupplyWriter::paintEvent(QPaintEvent *event)
{
    //????????????????????????
//    setWindowOpacity(1.0);

    QFont font("Microsoft YaHei", 12, 10, true);

    // ???????????????
    int watermark_width = 200;
    int watermark_height = 120;
    //????????????
    int watermark_inclination_angle = 30.0;

    QString content = QString("CGPRINTECH\n%1\t%2").arg(ui->username->text()).arg(QDate::currentDate().toString("yyyy-MM-dd"));

    //???????????????
    qreal ang = -watermark_inclination_angle;

    int width = this->width() * 1.5;
    int height = this->height() * 1.5;

    int x_step = watermark_width;
    int y_step = watermark_height;

    //??????????????????
    int row_count = width / y_step;
    //?????????????????? ????????????????????????????????????????????????????????????
    int col_count = height / x_step;

    for (int r = 0; r < row_count; r++)
    {
        for (int c = 0; c < col_count; c++)
        {
            QPainter p(this);
            p.setFont(font);
            p.setPen("#a0a0a0");
            p.translate(x_step * c, y_step * r);
            p.rotate(ang);
            p.drawText(QRect(0, 0, watermark_width, watermark_height), Qt::TextWordWrap, content);
        }
    }
    QRect rect = event->rect();
    rect.setRect(0, 0, 720, 540);
}
#else
void SupplyWriter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}
#endif
//?????????????????????????????????
void SupplyWriter::slotUpdateWaterMark()
{
    this->repaint();
}

SupplyWriter::~SupplyWriter()
{
    if (worker)
    {
        worker->quit();
        worker->wait(0);
    }

    if (tcpSocket[0])
         delete tcpSocket[0];
    if (tcpSocket[1])
        delete tcpSocket[1];

    if (trayIcon)
        delete trayIcon;

    delete timer;
    delete player;
    delete ui;
}

void SupplyWriter::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        is_drag = true;
        //???????????????????????????
        mouse_start_point = event->globalPos();
        //???????????????????????????
        window_start_point = this->frameGeometry().topLeft();
    }
}

void SupplyWriter::mouseMoveEvent(QMouseEvent *event)
{
    //???????????????????????????
    if (is_drag)
    {
        //???????????????????????????
        QPoint move_distance = event->globalPos() - mouse_start_point;
        //?????????????????????
        this->move(window_start_point + move_distance);
    }
}

void SupplyWriter::mouseReleaseEvent(QMouseEvent *event)
{
    //???????????????????????????
    if (event->button() == Qt::LeftButton)
    {
        is_drag = false;
    }
}

int SupplyWriter::StringToHex(char *str, unsigned char *out, unsigned int *outlen)
{
    char *p = str;
    char high = 0, low = 0;
    int tmplen = strlen(p), cnt = 0;
    tmplen = strlen(p);

    while (cnt < (tmplen / 2))
    {
        high =  ((*p > '9') && ((*p <= 'F') || (*p <= 'f'))) ? *p - 48 - 7 : *p - 48;
        low = (*(++p) > '9' && ((*p <= 'F') || (*p <= 'f'))) ? *(p) - 48 - 7 : *(p) - 48;
        out[cnt] = ((high & 0x0f) << 4 | (low & 0x0f));
        p++;
        cnt++;
    }

    if (tmplen % 2 != 0)
        out[cnt] = ((*p > '9') && ((*p <= 'F') || (*p <= 'f'))) ? *p - 48 - 7 : *p - 48;

    if (outlen != NULL)
        *outlen = tmplen / 2 + tmplen % 2;

    return tmplen / 2 + tmplen % 2;
}

void SupplyWriter::Pack16(unsigned char *dst, unsigned int val)
{
    dst[0] = (unsigned char)((val >> 8) & 0xff);
    dst[1] = (unsigned char)(val & 0xff);
}

void SupplyWriter::Pack32(unsigned char *dst, unsigned int val)
{
    dst[0] = (unsigned char)((val >> 24) & 0xff);
    dst[1] = (unsigned char)((val >> 16) & 0xff);
    dst[2] = (unsigned char)((val >> 8) & 0xff);
    dst[3] = (unsigned char)(val & 0xff);
}

unsigned int SupplyWriter::Unpack16(unsigned char *src)
{
    return (((unsigned int)src[0]) << 8
          | ((unsigned int)src[1]));
}

unsigned int SupplyWriter::Unpack32(unsigned char *src)
{
    return(((unsigned int)src[0]) << 24
         | ((unsigned int)src[1]) << 16
         | ((unsigned int)src[2]) << 8
         | (unsigned int)src[3]);
}

void SupplyWriter::hex_dump(const unsigned char *src, size_t length)
{
    int i = 0;
    const unsigned char *address = src;
    unsigned int num=0;
    size_t line_size=16;

    printf("%08x | ", num);
    num += 16;
    while (length-- > 0)
    {
        printf("%02x ", *address++);

        if ((i+1)%8==0 && (i+1)%16==8)
        {
            printf("  ");
        }

        if (!(++i % line_size) || (length == 0 && i % line_size))
        {
            printf("\n");

            if (length > 0)
            {
                printf("%08x | ", num);
                num += 16;
            }
        }
    }
    printf("\n");
}

//??????????????????????????????
bool SupplyWriter::check_input_valid()
{
    if (ui->lineEdit_2->text().length() == 0 ||
        ui->lineEdit_3->text().length() == 0 ||
        ui->lineEdit_13->text().length() == 0)
        return 0;

    if (check_modelid_valid(ui->lineEdit_2->text()) == 0)
        return false;

    if (check_serialno_valid(ui->lineEdit_3->text()) == 0)
        return false;

    return true;
}

void SupplyWriter::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);

    while(QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void SupplyWriter::slotConnected()
{
//    qDebug() << "Connected";
    this->server_status = _SUCCESS_STATUS;
}

void SupplyWriter::print_chip_info(struct cgprintech_supply_info_readback *supply_info)
{
    printf("model_id\t%s\n", supply_info->model_id);
    printf("serial_no\t%s\n", supply_info->serial_no);
    printf("marketing_area\t%s\n", supply_info->marketing_area);
    printf("manufacturer\t%s\n", supply_info->manufacturer);
    printf("trade_mark\t%s\n", supply_info->trade_mark);
    printf("type\t%s\n", supply_info->type);
    printf("pages\t%d\n", Unpack32(supply_info->pages));
    printf("dots\t%d\n", Unpack32(supply_info->dots));
    printf("product_date\t%02x%02x%02x%02x\n", supply_info->product_date[0],
        supply_info->product_date[1],
        supply_info->product_date[2],
        supply_info->product_date[3]);
    printf("beyond_pages\t%d\n", Unpack16(supply_info->beyond_pages));
    printf("beyond_percent\t%d\n", Unpack16(supply_info->beyond_percent));
    printf("free_pages\t%d\n", Unpack16(supply_info->free_pages));

    printf("install_date\t%02x%02x%02x%02x\n", supply_info->install_date[0],
        supply_info->install_date[1],
        supply_info->install_date[2],
        supply_info->install_date[3]);
    printf("recent_date\t%02x%02x%02x%02x\n", supply_info->recent_date[0],
        supply_info->recent_date[1],
        supply_info->recent_date[2],
        supply_info->recent_date[3]);
    printf("printed beyond pages\t%d\n", Unpack32(supply_info->print_beyond_pages));
    printf("printed_pages\t%d\n", Unpack32(supply_info->printed_pages));
    printf("printed_dots\t%d\n", Unpack16(supply_info->printed_dots));
}

void SupplyWriter::dataReceived()
{
    unsigned char resp[sizeof(MsgHdr) + SUPPLY_INFO_READBACK_LEN];
    qint64 length;

    while (tcpSocket[1]->bytesAvailable() > 0)
    {
        QByteArray datagram;
        length = tcpSocket[1]->bytesAvailable();
//        qDebug() << "bytesAvailable" << length;

        datagram.resize(tcpSocket[1]->bytesAvailable());
        tcpSocket[1]->read(datagram.data(), datagram.size());
        memcpy(&resp, datagram.data(), length);
        tcpSocket[1]->close();

        if (((RespInfo*)resp)->ret == RESP_OK)
        {
            play_mp3_sound(QCoreApplication::applicationDirPath() + "/sound/done.mp3");
            if (((RespInfo*)resp)->cmd == OP_WRITE_INFO)
            {
                ui->label_2->setText("<p style=\"color:green;font-weight:bold\">???????????????</p>");
                ui->label_45->setText("<p style=\"color:green;font-size:45px;font-weight:bold\">??????</p>");

                ui->lineEdit_3->clear();
                ui->lineEdit_7->clear();
                ui->lineEdit_11->clear();
                ui->lineEdit_12->clear();
                ui->lineEdit_3->setFocus();
            }
            else if (((RespInfo*)resp)->cmd == OP_READ_TONER_INFO ||
                     ((RespInfo*)resp)->cmd == OP_READ_DRUM_INFO)
            {
                if (((RespInfo*)resp)->cmd == OP_READ_TONER_INFO)
                    ui->label_2->setText("<p style=\"color:green;font-weight:bold\">?????? ???????????????</p>");
                else if (((RespInfo*)resp)->cmd == OP_READ_DRUM_INFO)
                    ui->label_2->setText("<p style=\"color:green;font-weight:bold\">????????? ???????????????</p>");

                ui->label_45->setText("<p style=\"color:green;font-size:45px;font-weight:bold\">??????</p>");
                //????????????????????????
//                this->print_chip_info((struct cgprintech_supply_info_readback*)(resp + sizeof(RespInfo)));

                ReadBack *readback = new ReadBack();

                emit sendChipInfo((struct cgprintech_supply_info_readback*)(resp + sizeof(RespInfo)));
                emit sendThemeMode(this->theme_state);

                readback->show();
            }
//            this->Sleep(3000);
        }
        else
        {
            // operation failed
            if (((RespInfo*)resp)->cmd == OP_WRITE_INFO)
            {
                ui->label_2->setText("<p style=\"color:red;font-weight:bold\">???????????????</p>");
                ui->label_45->setText("<p style=\"color:red;font-size:45px;font-weight:bold\">????</p>");
            }
            else if (((RespInfo*)resp)->cmd == OP_READ_TONER_INFO ||
                     ((RespInfo*)resp)->cmd == OP_READ_DRUM_INFO)
            {
                if (((RespInfo*)resp)->cmd == OP_READ_TONER_INFO)
                {
                    ui->label_2->setText("<p style=\"color:red;font-weight:bold\">?????? ???????????????</p>");
                }
                else if (((RespInfo*)resp)->cmd == OP_READ_DRUM_INFO)
                {
                    ui->label_2->setText("<p style=\"color:red;font-weight:bold\">????????? ???????????????</p>");
                }

                ui->label_45->setText("<p style=\"color:red;font-size:45px;font-weight:bold\">????</p>");
            }
            play_mp3_sound(QCoreApplication::applicationDirPath() + "/sound/failed.mp3");

//            this->Sleep(3000);
        }

        server_status = _INVALID_PARA;
        break;
    }
}

//????????????????????????
bool SupplyWriter::sendData(int cmd, void* data, int data_len)
{
    uint8_t writeinfo[sizeof(MsgHdr) + data_len];

    if (tcpSocket[1] == NULL)
    {
        tcpSocket[1] = new QTcpSocket(this);
    }
    connect(tcpSocket[1], SIGNAL(connected()), this, SLOT(slotConnected()));
//    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(tcpSocket[1], SIGNAL(readyRead()), this, SLOT(dataReceived()));

    if (tcpSocket[1]->isOpen() == true)
    {
        tcpSocket[1]->close();
    }
    tcpSocket[1]->connectToHost(ui->lineEdit_1->text(), TCP_PORT, QIODevice::ReadWrite, QAbstractSocket::AnyIPProtocol);

    ((MsgHdr*)writeinfo)->cmd = cmd;
    ((MsgHdr*)writeinfo)->len = data_len;
    if (data)
    {
        if (strncasecmp(((struct cgprintech_supply_info*)data)->model_id, "TL", 2) == 0)
            ((MsgHdr*)writeinfo)->i2c_addr = _TONER_CHIP_ADDR;
        else if (strncasecmp(((struct cgprintech_supply_info*)data)->model_id, "DL", 2) == 0)
            ((MsgHdr*)writeinfo)->i2c_addr = _DRUM_CHIP_ADDR;

        memcpy(writeinfo + sizeof(MsgHdr), data, data_len);
//        this->hex_dump((unsigned char*)&writeinfo, sizeof(writeinfo));
    }
    else
    {
        if (cmd == OP_READ_TONER_INFO)
            ((MsgHdr*)writeinfo)->i2c_addr = _TONER_CHIP_ADDR;
        else if (cmd == OP_READ_DRUM_INFO)
            ((MsgHdr*)writeinfo)->i2c_addr = _DRUM_CHIP_ADDR;
    }

    if (tcpSocket[1]->write((const char*)&writeinfo, sizeof(writeinfo)) == -1)
    {
//        qDebug() << "write to tcp socket failed";
        return false;
    }

    return true;
}

void SupplyWriter::open_sql_server()
{
    if (db.isOpen())
    {
        //?????????????????????????????????????????????
        db.close();
    }

    db.setHostName(ui->lineEdit_14->text());
    db.setUserName(ui->lineEdit->text());
    db.setPassword(ui->lineEdit_4->text());
    db.setDatabaseName(ui->lineEdit_5->text());   //???????????????????????????

    if (db.open()) {
        ui->label_13->setText("<p style=\"color:green;font-weight:bold\">???????????????</p>");
        odbc_status = _SUCCESS_STATUS;
        return;
    } else {
        ui->label_13->setText("<p style=\"color:red;font-weight:bold\">???????????????</p>");
//        qDebug()<<"error open database because"<<db.lastError().text();
        odbc_status = _FAILED_STATUS;
        return;
    }
}

//???????????????
bool SupplyWriter::Insert_SupplyInfo_Sql()
{
    bool ret = _FAILED_STATUS;

    open_sql_server();
    if (odbc_status == _FAILED_STATUS)
    {
        return ret;
    }

    this->fill_supplyinfo_data();
    if (odbc_status == _FAILED_STATUS)
    {
        ui->label_13->setText("<p style=\"color:red;font-weight:bold\">????????????????????????</p>");
        return ret;
    }

    query = QSqlQuery(this->db);
    QString new_sql = QString("insert into %1.%2 (operator,model_id,serial_no,marketing_area,year,month,day,"
                              "manufacturer,trade_mark,type,pages,dots,overflow_pages,overflow_percent,free_pages)"
                              "values(:operator,:model_id,:serial_no,:marketing_area,:year,:month,:day,"
                              ":manufacturer,:trade_mark,:type,:pages,:dots,:overflow_pages,"
                              ":overflow_percent,:free_pages)").arg(DATABASE_NAME).arg(TABLE_NAME);

    query.prepare(new_sql);
    query.bindValue(":operator", login_user.toLocal8Bit().data());
    query.bindValue(":model_id", supply_info.model_id);
    query.bindValue(":serial_no", supply_info.serial_no);
    query.bindValue(":marketing_area", supply_info.marketing_area);
    query.bindValue(":year", this->year);
    query.bindValue(":month", this->month);
    query.bindValue(":day", this->day);
    query.bindValue(":manufacturer", supply_info.manufacturer);
    query.bindValue(":trade_mark", supply_info.trade_mark);
    query.bindValue(":type", supply_info.type);
    query.bindValue(":pages", Unpack32(supply_info.pages));
    query.bindValue(":dots", Unpack32(supply_info.dots));
    query.bindValue(":overflow_pages", Unpack16(supply_info.beyond_pages));
    query.bindValue(":overflow_percent", Unpack16(supply_info.beyond_percent));
    query.bindValue(":free_pages", Unpack16(supply_info.free_pages));
    ret = query.exec();
    if (ret)
    {
        play_mp3_sound(QCoreApplication::applicationDirPath() + "/sound/done.mp3");

        ui->label_13->setText("<p style=\"color:green;font-weight:bold\">???????????????</p>");
        ui->label_46->setText("<p style=\"color:green;font-size:45px;font-weight:bold\">??????</p>");
        ret = _SUCCESS_STATUS;
    }
    else
    {
        play_mp3_sound(QCoreApplication::applicationDirPath() + "/sound/failed.mp3");

        ui->label_13->setText("<p style=\"color:red;font-weight:bold\">???????????????????????????????????????</p>");
        ui->label_46->setText("<p style=\"color:red;font-size:45px;font-weight:bold\">????</p>");
        qDebug() << query.lastError().text() << QString(QObject::tr("????????????"));
        ret = _FAILED_STATUS;
    }

    this->Sleep(3000);
    ui->label_46->setText("");
    odbc_status = _INVALID_PARA;

    return ret;
}

//???????????????????????????????????????????????????
void SupplyWriter::on_QuerySqlButton_clicked()
{
    int num = 0;

    open_sql_server();
    if (odbc_status == _FAILED_STATUS)
    {
        return;
    }

    struct cgprintech_supply_sqlinfo ChipInfo;
    QString sqlcmd = QString("select model_id,serial_no,marketing_area,year,month,day,manufacturer,trade_mark,"
                             "type,pages,dots,overflow_pages,overflow_percent,free_pages,operator from %1.%2 "
                             "where serial_no='%3'").arg(DATABASE_NAME).arg(TABLE_NAME).arg(ui->lineEdit_3->text());
//    qDebug() << sqlcmd;
    query = QSqlQuery(this->db);
    if (!query.exec(sqlcmd))
    {
        qDebug() << query.lastError().driverText() << QString(QObject::tr("????????????"));
        return;
    }
    else
    {
        while (query.next())
        {
            num++;

            memcpy(ChipInfo.model_id, query.value(0).toString().toLatin1().data(), 16);
            memcpy(ChipInfo.serial_no, query.value(1).toString().toLatin1().data(), 32);
            memcpy(ChipInfo.marketing_area, query.value(2).toString().toLatin1().data(), 4);
            QString date = query.value(3).toString() + "." + query.value(4).toString() + "." + query.value(5).toString();
            memcpy(ChipInfo.product_date, date.toLatin1().data(), 12);
            memcpy(ChipInfo.manufacturer, query.value(6).toString().toLatin1().data(), 16);
            memcpy(ChipInfo.trade_mark, query.value(7).toString().toLatin1().data(), 16);
            memcpy(ChipInfo.type, query.value(8).toString().toLatin1().data(), 4);
            memcpy(ChipInfo.pages, query.value(9).toString().toLatin1().data(), 12);
            memcpy(ChipInfo.dots, query.value(10).toString().toLatin1().data(), 12);
            memcpy(ChipInfo.overflow_pages, query.value(11).toString().toLatin1().data(), 4);
            memcpy(ChipInfo.overflow_percent, query.value(12).toString().toLatin1().data(), 4);
            memcpy(ChipInfo.free_pages, query.value(13).toString().toLatin1().data(), 4);
            ChipInfo.operator_id = query.value(14).toString();
            qDebug() << query.value(14).toString();
        }
    }

    if (num == 0)
    {
        play_mp3_sound(QCoreApplication::applicationDirPath() + "/sound/failed.mp3");
        ui->label_13->setText("<p style=\"color:red;font-weight:bold\">?????????????????????</p>");
        ui->label_46->setText("<p style=\"color:red;font-size:45px;font-weight:bold\">????</p>");
        this->Sleep(3000);
        ui->label_46->setText("");
        return;
    }

    play_mp3_sound(QCoreApplication::applicationDirPath() + "/sound/done.mp3");
    ui->label_13->setText("<p style=\"color:green;font-weight:bold\">?????????????????????</p>");
    ui->label_46->setText("<p style=\"color:green;font-size:45px;font-weight:bold\">??????</p>");

    SqlChipInfo *sqlinfo = new SqlChipInfo();
    emit sendThemeMode(theme_state);
    emit sendSqlInfo(&ChipInfo);
    sqlinfo->show();

    this->Sleep(3000);
    ui->label_46->clear();
    odbc_status = _INVALID_PARA;
}

//????????????
void SupplyWriter::write_supplyinfo2chip()
{
    this->fill_supplyinfo_data();
    this->sendData(OP_WRITE_INFO, &supply_info, CGPRINTECH_SUPPLY_INFO_LEN);
}

void SupplyWriter::fill_supplyinfo_data()
{
    unsigned int len;
    char date[8] = {0};

    memset(&supply_info, 0, CGPRINTECH_SUPPLY_INFO_LEN);
    if (check_input_valid() == 0)
    {
        return;
    }

    memcpy(&supply_info.model_id, ui->lineEdit_2->text().toLatin1().data(), ui->lineEdit_2->text().length());
    memcpy(&supply_info.serial_no, ui->lineEdit_3->text().toLatin1().data(), ui->lineEdit_3->text().length());
    memcpy(&supply_info.manufacturer, ui->comboBox_3->currentText().toLatin1().data(), ui->comboBox_3->currentText().length());
    memcpy(&supply_info.trade_mark, ui->comboBox_4->currentText().toLatin1().data(), ui->comboBox_4->currentText().length());
    memcpy(&supply_info.marketing_area, ui->lineEdit_7->text().toLatin1().data(), 2);
    memcpy(&supply_info.type, ui->lineEdit_13->text().toLatin1().data(), 1);

    Pack32(supply_info.pages, ui->lineEdit_6->text().toUInt());
    Pack16(supply_info.beyond_pages, ui->lineEdit_11->text().toUInt());
    Pack16(supply_info.free_pages, ui->lineEdit_12->text().toUInt());

    year = ui->dateEdit->date().year();
    month = ui->dateEdit->date().month();
    day = ui->dateEdit->date().day();
    sprintf(date, "%04d%02d%02d", year, month, day);
    this->StringToHex(date, supply_info.product_date, &len);

//    this->hex_dump((unsigned char*)&supply_info, sizeof(struct cgprintech_supply_info));
}

//????????????????????????
void SupplyWriter::on_ReadTonerInfo_clicked()
{
    check_server_status();
    if (this->server_status == _FAILED_STATUS)
        return;

    //1.??????????????????????????????
    this->sendData(OP_READ_TONER_INFO, NULL, 0);
    return;
}

//???????????????????????????
void SupplyWriter::on_ReadDrumInfo_clicked()
{
    check_server_status();
    if (this->server_status == _FAILED_STATUS)
        return;

    //1.??????????????????????????????
    this->sendData(OP_READ_DRUM_INFO, NULL, 0);
    return;
}

bool SupplyWriter::check_modelid_valid(QString modelid)
{
    QRegExp rx3("^[TD]L-34[01][UHL]?$");
    if (!rx3.exactMatch(modelid))
    {
        return false;
    }
    return true;
}

bool SupplyWriter::check_serialno_valid(QString serialno)
{
    QRegExp rx4("^CGL?[0-9]{10}CGRX[ABCDFGHJKLMNPQRSTWXYZ][1-9A-C][1-9A-V][0-9]{4}$");
    if (!rx4.exactMatch(serialno))
    {
        return false;
    }
    return true;
}

//??????IP??????????????????
bool SupplyWriter::checkIpValid(int version, QString ip)
{
    if (version == 4)
    {
        QRegExp rx2("^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$");
        if(rx2.exactMatch(ip))
        {
            //ip????????????
            return true;
        }
    }
    else if (version == 6)
    {
        QRegExp rx2("^([\\da-fA-F]{1,4}:){6}((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}"
                    "(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$|^::([\\da-fA-F]{1,4}:){0,4}"
                    "((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}"
                    "(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$|^([\\da-fA-F]{1,4}:):([\\da-fA-F]{1,4}:){0,3}"
                    "((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}"
                    "(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$|^([\\da-fA-F]{1,4}:){2}:([\\da-fA-F]{1,4}:){0,2}"
                    "((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}"
                    "(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$|^([\\da-fA-F]{1,4}:){3}:([\\da-fA-F]{1,4}:){0,1}"
                    "((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}"
                    "(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$|^([\\da-fA-F]{1,4}:){4}:"
                    "((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}"
                    "(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$|^([\\da-fA-F]{1,4}:){7}[\\da-fA-F]{1,4}$|^:((:[\\da-fA-F]{1,4}){1,6}|:)$|^[\\da-fA-F]{1,4}:"
                    "((:[\\da-fA-F]{1,4}){1,5}|:)$|^([\\da-fA-F]{1,4}:){2}"
                    "((:[\\da-fA-F]{1,4}){1,4}|:)$|^([\\da-fA-F]{1,4}:){3}"
                    "((:[\\da-fA-F]{1,4}){1,3}|:)$|^([\\da-fA-F]{1,4}:){4}"
                    "((:[\\da-fA-F]{1,4}){1,2}|:)$|^([\\da-fA-F]{1,4}:){5}:([\\da-fA-F]{1,4})?$|^([\\da-fA-F]{1,4}:){6}:$");
        if(rx2.exactMatch(ip))
        {
            //ip????????????
            return true;
        }
    }

    return false;
}

//??????IP???????????????
int SupplyWriter::checkIPversion(QString IP)
{
    if (IP.contains(":", Qt::CaseInsensitive))
        return 6;
    else if (IP.contains(".", Qt::CaseInsensitive))
        return 4;

    return 0;
}

void SupplyWriter::statusReceived()
{
    RespInfo resp;
    qint64 length;

    while (tcpSocket[0]->bytesAvailable() > 0)
    {
        QByteArray datagram;
        length = tcpSocket[0]->bytesAvailable();

        datagram.resize(tcpSocket[0]->bytesAvailable());
        tcpSocket[0]->read(datagram.data(), datagram.size());
        memcpy(&resp, datagram.data(), length);
        tcpSocket[0]->close();

//        qDebug() << resp.cmd << resp.ret;
        switch (resp.ret)
        {
        case RESP_NO_DETECT:
            ui->label_2->setText(tr("<font style='color:red; font:bold;'>%1</font>").arg(QStringLiteral("??????????????????????????????")));
//            ui->label_45->setText("<p style=\"color:red;font-size:45px;font-weight:bold\">??????</p>");
            ui->label_45->clear();
            ui->ReadDrumInfo->setEnabled(false);
            ui->ReadTonerInfo->setEnabled(false);
            //??????????????????????????????
            break;
        case RESP_NO_TONER_DETECT:
            ui->label_2->setText(tr("<font style='color:green; font:bold;'>%1</font>").arg(QStringLiteral("?????????????????????")) +
                                 tr("<font style='color:red; font:bold;'>%1</font>").arg(QStringLiteral("??????????????????")));
//            ui->label_45->setText("<p style=\"color:blue;font-size:45px;font-weight:bold\">\?\?</p>");
            ui->label_45->clear();
            ui->ReadDrumInfo->setEnabled(true);
            ui->ReadTonerInfo->setEnabled(false);
            //?????????????????????
            break;
        case RESP_NO_DRUM_DETECT:
            ui->label_2->setText(tr("<font style='color:green; font:bold;'>%1</font>").arg(QStringLiteral("??????????????????")) +
                                 tr("<font style='color:red; font:bold;'>%1</font>").arg(QStringLiteral("?????????????????????")));
//            ui->label_45->setText("<p style=\"color:blue;font-size:45px;font-weight:bold\">\?\?</p>");
            ui->label_45->clear();
            ui->ReadDrumInfo->setEnabled(false);
            ui->ReadTonerInfo->setEnabled(true);
            //??????????????????
            break;
        case RESP_ALL_DETECT:
        default:
            //?????????????????????????????????????????????
            ui->label_2->setText("<p style=\"color:green;font-weight:bold\">??????????????????????????????</p>");
//            ui->label_45->setText("<p style=\"color:green;font-size:45px;font-weight:bold\">??????</p>");
            ui->label_45->clear();
            ui->ReadDrumInfo->setEnabled(true);
            ui->ReadTonerInfo->setEnabled(true);
            break;
        }

        break;
    }
}

//????????????????????????????????????
//??????false?????????????????????true????????????
bool SupplyWriter::check_server_status()
{
    tcpSocket[0] = new QTcpSocket(this);
    this->server_status = _FAILED_STATUS;
    MsgHdr hdr;

    connect(tcpSocket[0], SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(tcpSocket[0], SIGNAL(readyRead()), this, SLOT(statusReceived()));

    if (tcpSocket[0]->isOpen() == true)
    {
        tcpSocket[0]->close();
    }
    tcpSocket[0]->connectToHost(ui->lineEdit_1->text(), TCP_PORT, QIODevice::ReadWrite, QAbstractSocket::AnyIPProtocol);

    if (server_status)
    {
        hdr.cmd = OP_GET_STATUS;
        hdr.len = 0;
        hdr.i2c_addr = 0;

        if (tcpSocket[0]->write((const char*)&hdr, sizeof(hdr)) == -1)
        {
            qDebug() << "send data failed";
            return false;
        }
    }

    this->Sleep(100);
    return server_status;
}

//????????????
void SupplyWriter::on_AboutButton_clicked()
{
    QDate date = QDate::fromString("20221210", "yyyyMMdd");

    QString info = QString("???????????????v2.2\n"
                           "???????????????%1\n"
                           "?????? Qt 5.14.2 ?????? by youshun\n\n"
                           "????????? ????????????????????????????????????????????????????????????\n"
                           "?????????????????????????????? ????????????\n").arg(date.toString("yyyy-MM-dd"));

    QMessageBox::about(this, tr("?????? ??????????????????"), info);
}

//???????????????
void SupplyWriter::on_CloseButton_clicked()
{
    this->accept();
}

//??????????????????
void SupplyWriter::on_HelpButton_clicked()
{
    HelpDialog* help = new HelpDialog();
    emit sendThemeMode(this->theme_state);
    help->show();
}

//??????????????????????????????
void SupplyWriter::on_DeleteSqlButton_clicked()
{
    open_sql_server();
    if (odbc_status == _FAILED_STATUS)
    {
        ui->label_13->setText("<p style=\"color:red;font-weight:bold\">????????????????????????</p>");
        return;
    }

    QString sqlcmd = QString("delete from %1.%2 where serial_no='%3'").arg(DATABASE_NAME).arg(TABLE_NAME).arg(ui->lineEdit_3->text());
    qDebug() << sqlcmd;
    query = QSqlQuery(this->db);
    bool ret = query.exec(sqlcmd);

    if (ret == true)
        ui->label_13->setText("<p style=\"color:green;font-weight:bold\">??????????????????????????????</p>");
    else
        ui->label_13->setText("<p style=\"color:red;font-weight:bold\">??????????????????????????????</p>");
}

//?????????????????????????????????????????????????????????
void SupplyWriter::on_LoginButton_clicked()
{
    if (ui->username->text().length() == 0 ||
        ui->password->text().length() == 0)
    {
        ui->label_21->setText("<p style=\"color:red;font-weight:bold\">?????????????????????????????????</p>");
        return;
    }

    QString strmd5_username = QCryptographicHash::hash(ui->username->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();
    QString strmd5_password = QCryptographicHash::hash(ui->password->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();

    setting.beginGroup(strmd5_username);
    if (setting.value("name").toString().compare(strmd5_username, Qt::CaseInsensitive) != 0)
    {
        ui->label_21->setText("<p style=\"color:red;font-weight:bold\">?????????????????????</p>");
        setting.endGroup();
        return;
    }
    if (setting.value("pwd").toString().compare(strmd5_password, Qt::CaseInsensitive) != 0)
    {
        ui->label_21->setText("<p style=\"color:red;font-weight:bold\">??????????????????</p>");
        setting.endGroup();
        return;
    }
    //????????????????????????
    QString strmd5_recently = QCryptographicHash::hash(QDate::currentDate().toString("yyyy/M/d").toLocal8Bit(), QCryptographicHash::Md5).toHex();
    setting.setValue("recent", strmd5_recently);
    login_user = ui->username->text();
    setting.endGroup();

    this->clear_main_page();
    ui->stackedWidget->setCurrentIndex(1);
//    this->create_start_monitor();
}

//????????????
void SupplyWriter::on_ExitButton_clicked()
{
    this->accept();
}

//????????????
void SupplyWriter::on_CreateUser_clicked()
{
    ui->username->clear();
    ui->stackedWidget->setCurrentIndex(2);
    this->clear_newuser_page();
}

//????????????????????????
void SupplyWriter::on_ResetPassword_clicked()
{
    ui->username->clear();
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget_2->setCurrentIndex(0);
    this->clear_resetpwd_page0();
}

//????????????
void SupplyWriter::on_ModifyPassword_clicked()
{
    ui->username->clear();
    ui->stackedWidget->setCurrentIndex(3);
    this->clear_renewpwd_page();
}

//?????????????????????????????????
void SupplyWriter::on_Return_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->clear_login_page();
}

//?????????????????????
//?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
//??????????????????
void SupplyWriter::on_Confirm_clicked()
{
    if (ui->lineEdit_8->text().length() == 0 ||
        ui->lineEdit_9->text().length() == 0 ||
        ui->lineEdit_10->text().length() == 0)
    {
        ui->label_26->setText("<p style=\"color:red;font-weight:bold\">?????????????????????????????????</p>");
        return;
    }
    if (ui->lineEdit_9->text().compare(ui->lineEdit_10->text(), Qt::CaseSensitive) != 0)
    {
        ui->label_26->setText("<p style=\"color:red;font-weight:bold\">????????????????????????</p>");
        return;
    }
    QString strmd5_username = QCryptographicHash::hash(ui->lineEdit_8->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();
    QString strmd5_password = QCryptographicHash::hash(ui->lineEdit_9->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();
    QString strmd5_register = QCryptographicHash::hash(QDate::currentDate().toString("yyyy/M/d").toLocal8Bit(), QCryptographicHash::Md5).toHex();
    QString strmd5_recently = QCryptographicHash::hash(QDate::currentDate().toString("yyyy/M/d").toLocal8Bit(), QCryptographicHash::Md5).toHex();

    setting.beginGroup(strmd5_username);
    if (setting.value("name").toString().compare(strmd5_username, Qt::CaseInsensitive) == 0)
    {
        ui->label_26->setText("<p style=\"color:red;font-weight:bold\">??????????????????????????????????????????</p>");
        setting.endGroup();
        return;
    }
    setting.setValue("name", strmd5_username);
    setting.setValue("pwd", strmd5_password);
    setting.setValue("origin", strmd5_register);
    setting.setValue("recent", strmd5_recently);
    setting.endGroup();

    ui->label_26->setText("<p style=\"color:green;font-weight:bold\">????????????????????? 3 ????????????????????????</p>");
    ui->Confirm->setDisabled(true);
    ui->Return->setDisabled(true);
    this->Sleep(3000);
    ui->stackedWidget->setCurrentIndex(0);
    this->clear_login_page();
}

//??????????????????
void SupplyWriter::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->clear_login_page();
}

//??????????????????
void SupplyWriter::on_pushButton_3_clicked()
{
    if (ui->lineEdit_15->text().length() == 0 ||
        ui->lineEdit_16->text().length() == 0 ||
        ui->lineEdit_17->text().length() == 0 ||
        ui->lineEdit_18->text().length() == 0)
    {
        ui->label_31->setText("<p style=\"color:red;font-weight:bold\">???????????????????????????</p>");
        return;
    }

    if (ui->lineEdit_17->text().compare(ui->lineEdit_18->text(), Qt::CaseSensitive) != 0)
    {
        ui->label_31->setText("<p style=\"color:red;font-weight:bold\">???????????????</p>");
        return;
    }

    QString strmd5_username = QCryptographicHash::hash(ui->lineEdit_15->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();
    QString strmd5_password = QCryptographicHash::hash(ui->lineEdit_16->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();
    QString strmd5_newpwd = QCryptographicHash::hash(ui->lineEdit_17->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();

    setting.beginGroup(strmd5_username);
    if (setting.value("name").toString().compare(strmd5_username, Qt::CaseInsensitive) != 0)
    {
        ui->label_31->setText("<p style=\"color:red;font-weight:bold\">?????????????????????</p>");
        setting.endGroup();
        return;
    }

    if (setting.value("pwd").toString().compare(strmd5_password, Qt::CaseInsensitive) != 0)
    {
        ui->label_31->setText("<p style=\"color:red;font-weight:bold\">?????????????????????</p>");
        setting.endGroup();
        return;
    }

    setting.setValue("pwd", strmd5_newpwd);
    setting.endGroup();

    ui->label_31->setText("<p style=\"color:green;font-weight:bold\">??????????????????????????? 3 ????????????????????????</p>");
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    this->Sleep(3000);
    ui->stackedWidget->setCurrentIndex(0);
    this->clear_login_page();
}

//??????????????????
void SupplyWriter::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->clear_login_page();
}

//???????????????????????????????????????????????????????????????????????????????????????
void SupplyWriter::on_pushButton_8_clicked()
{
    if (ui->lineEdit_19->text().length() == 0)
    {
        ui->label_41->setText("<p style=\"color:red;font-weight:bold\">????????????????????????</p>");
        return;
    }

    resetpwd_username = QCryptographicHash::hash(ui->lineEdit_19->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();

    setting.beginGroup(resetpwd_username);
    if (setting.value("name").toString().compare(resetpwd_username, Qt::CaseInsensitive) != 0)
    {
        ui->label_41->setText("<p style=\"color:red;font-weight:bold\">?????????????????????</p>");
        setting.endGroup();
        return;
    }

    QString strmd5_register = QCryptographicHash::hash(ui->dateEdit_2->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();
    QString strmd5_recently = QCryptographicHash::hash(ui->dateEdit_3->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();

    if (setting.value("origin").toString().compare(strmd5_register, Qt::CaseInsensitive) != 0)
    {
        ui->label_41->setText("<p style=\"color:red;font-weight:bold\">?????????????????????????????????????????????</p>");
        setting.endGroup();
        return;
    }

    if (setting.value("recent").toString().compare(strmd5_recently, Qt::CaseInsensitive) != 0)
    {
        ui->label_41->setText("<p style=\"color:red;font-weight:bold\">???????????????????????????????????????????????????</p>");
        setting.endGroup();
        return;
    }
    setting.endGroup();

    ui->stackedWidget_2->setCurrentIndex(1);
    this->clear_resetpwd_page1();
}

//??????????????????
void SupplyWriter::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->clear_login_page();
}

//??????????????????
void SupplyWriter::on_pushButton_10_clicked()
{
    if (ui->lineEdit_20->text().length() == 0 ||
        ui->lineEdit_21->text().length() == 0)
    {
        ui->label_40->setText("<p style=\"color:red;font-weight:bold\">?????????????????????</p>");
        return;
    }

    if (ui->lineEdit_20->text().compare(ui->lineEdit_21->text(), Qt::CaseSensitive) != 0)
    {
        ui->label_40->setText("<p style=\"color:red;font-weight:bold\">????????????????????????</p>");
        return;
    }

    QString strmd5_password = QCryptographicHash::hash(ui->lineEdit_20->text().toLocal8Bit(), QCryptographicHash::Md5).toHex();
    setting.beginGroup(resetpwd_username);
    setting.setValue("pwd", strmd5_password);
    setting.endGroup();

    ui->label_40->setText("<p style=\"color:green;font-weight:bold\">??????????????????????????? 3 ????????????????????????</p>");
    ui->pushButton_9->setDisabled(true);
    ui->pushButton_10->setDisabled(true);

    this->Sleep(3000);
    ui->stackedWidget->setCurrentIndex(0);
    this->clear_login_page();
}

void SupplyWriter::adjust_bright_pixmap(int bright)
{
    QImage image[4];
    QImage new_image[4];

    image[0] = pixmap[1].toImage();
    image[1] = pixmap[2].toImage();
    image[2] = pixmap[3].toImage();
    image[3] = pixmap[4].toImage();

    new_image[0] = adjust_bright(bright, image[0]);
    new_image[1] = adjust_bright(bright, image[1]);
    new_image[2] = adjust_bright(bright, image[2]);
    new_image[3] = adjust_bright(bright, image[3]);

    ui->title_label->setPixmap(QPixmap::fromImage(new_image[0]));
    ui->label_24->setPixmap(QPixmap::fromImage(new_image[1]));
    ui->label_32->setPixmap(QPixmap::fromImage(new_image[2]));
    ui->label_27->setPixmap(QPixmap::fromImage(new_image[3]));
}

void SupplyWriter::on_checkBox_stateChanged(int state)
{
    this->theme_state = state;
    if (state == 2)
    {
        this->set_style_sheet("dark.qss");
        adjust_bright_pixmap(-80);
    }
    else if (state == 0)
    {
        this->set_style_sheet("light.qss");
        adjust_bright_pixmap(0);
    }
}

void SupplyWriter::on_lineEdit_2_textChanged(const QString &arg1)
{
    if (arg1.length() < 6)
    {
        ui->lineEdit_6->setText("");
        return;
    }
    ui->lineEdit_7->setText("CN");

    QRegExp rxt1("^TL-34[01]{1}L$");
    QRegExp rxt0("^TL-34[01]{1}$");
    QRegExp rxt2("^TL-34[01]{1}H$");
    QRegExp rxt3("^TL-340U$");
    QRegExp rxd0("^DL-34[01]{1}$");

    if (rxt1.exactMatch(arg1))
    {
        ui->lineEdit_6->setText("1500");
        ui->lineEdit_11->setText("45");
        return;
    }

    if (rxt0.exactMatch(arg1))
    {
        ui->lineEdit_6->setText("3000");
        ui->lineEdit_11->setText("90");
        return;
    }

    if (rxt2.exactMatch(arg1))
    {
        ui->lineEdit_6->setText("5500");
        ui->lineEdit_11->setText("165");
        return;
    }

    if (rxt3.exactMatch(arg1))
    {
        ui->lineEdit_6->setText("15000");
        ui->lineEdit_11->setText("450");
        return;
    }

    if (rxd0.exactMatch(arg1))
    {
        ui->lineEdit_6->setText("30000");
        ui->lineEdit_11->setText("0");
        return;
    }

    ui->lineEdit_6->clear();
    ui->lineEdit_11->clear();
}

void SupplyWriter::on_lineEdit_3_textChanged(const QString &arg1)
{
    bool ok_status = false;

    if (arg1.mid(0, 3).compare("CGL", Qt::CaseSensitive) == 0)
        ui->lineEdit_13->setText("I");
    else if (arg1.mid(0, 2).compare("CG", Qt::CaseSensitive) == 0)
        ui->lineEdit_13->setText("M");
    else
        ui->lineEdit_13->clear();

    ui->lineEdit_12->setText("20");

    if (arg1.contains("L2090000045", Qt::CaseSensitive) ||
        arg1.contains("0301000259", Qt::CaseSensitive))
    {
        ui->lineEdit_2->setText("TL-341L");
        ok_status = true;
        goto THE_END;
    }

    if (arg1.contains("L2090000046", Qt::CaseSensitive) ||
        arg1.contains("0301000260", Qt::CaseSensitive))
    {
        ui->lineEdit_2->setText("TL-341");
        ok_status = true;
        goto THE_END;
    }

    if (arg1.contains("0301000261", Qt::CaseSensitive) == true)
    {
        ui->lineEdit_2->setText("TL-341H");
        ok_status = true;
        goto THE_END;
    }

    if (arg1.contains("L2090000052", Qt::CaseSensitive) ||
        arg1.contains("0301000224", Qt::CaseSensitive))
    {
        ui->lineEdit_2->setText("TL-340L");
        ok_status = true;
        goto THE_END;
    }

    if (arg1.contains("L2090000053", Qt::CaseSensitive) ||
        arg1.contains("0301000223", Qt::CaseSensitive))
    {
        ui->lineEdit_2->setText("TL-340");
        ok_status = true;
        goto THE_END;
    }

    if (arg1.contains("0301000225", Qt::CaseSensitive) == true)
    {
        ui->lineEdit_2->setText("TL-340H");
        ok_status = true;
        goto THE_END;
    }

    if (arg1.contains("0301000226", Qt::CaseSensitive) == true)
    {
        ui->lineEdit_2->setText("TL-340U");
        ok_status = true;
        goto THE_END;
    }

    if (arg1.contains("L2090000049", Qt::CaseSensitive) ||
        arg1.contains("0204000131", Qt::CaseSensitive))
    {
        ui->lineEdit_2->setText("DL-340");
        ok_status = true;
        goto THE_END;
    }

    if (arg1.contains("L2090000051", Qt::CaseSensitive) ||
        arg1.contains("0204000258", Qt::CaseSensitive))
    {
        ui->lineEdit_2->setText("DL-341");
        ok_status = true;
        goto THE_END;
    }

THE_END:
    if (ok_status)
    {
        if (ui->lineEdit_1->text().length() &&
            check_serialno_valid(ui->lineEdit_3->text()) &&
            working_mode == _AUTO_WRITE_MODE)
        {
            if ((ui->lineEdit_2->text().mid(0, 2).compare("DL", Qt::CaseSensitive) == 0 && ui->ReadDrumInfo->isEnabled()) ||
                (ui->lineEdit_2->text().mid(0, 2).compare("TL", Qt::CaseSensitive) == 0 && ui->ReadTonerInfo->isEnabled()))
            {
                if (this->Insert_SupplyInfo_Sql() == _FAILED_STATUS)
                {
                    qDebug() << "insert into database failed";
                    return;
                }

                timer->stop();
                write_supplyinfo2chip();
                timer->start(3000);
            }
        }
    }
    else
    {
        ui->lineEdit_2->setText("");
    }
}

//??????IP???????????????????????????????????????????????????
void SupplyWriter::on_lineEdit_1_textChanged(const QString &arg1)
{
    if (arg1.length() && checkIpValid(checkIPversion(arg1), arg1))
    {
        if (tcpSocket[0])
        {
            tcpSocket[0]->close();
            delete tcpSocket[0];
            tcpSocket[0] = NULL;
        }

        if (check_server_status() == _FAILED_STATUS)
        {
            ui->label_2->setText("<p style=\"color:red;font-weight:bold\">???????????????</p>");
            ui->label_45->clear();
            ui->ReadDrumInfo->setEnabled(false);
            ui->ReadTonerInfo->setEnabled(false);
            return;
        }
    }
    else
    {
        ui->label_2->setText("<p style=\"color:red;font-weight:bold\">IP??????????????????</p>");
        ui->label_45->clear();
        ui->ReadDrumInfo->setEnabled(false);
        ui->ReadTonerInfo->setEnabled(false);
    }
}

void SupplyWriter::try_connect_db()
{
    emit send_db_config(ui->lineEdit_14->text(), ui->lineEdit->text(),
                        ui->lineEdit_4->text(), ui->lineEdit_5->text());

    if (ui->lineEdit->text().length() &&
        ui->lineEdit_14->text().length() &&
        ui->lineEdit_4->text().length() &&
        ui->lineEdit_5->text().length() &&
        checkIpValid(checkIPversion(ui->lineEdit_14->text()), ui->lineEdit_14->text()))
    {
        open_sql_server();
    }
    else
    {
        odbc_status = _INVALID_PARA;
        ui->label_13->setText("<p style=\"color:red;font-weight:bold\">??????????????????</p>");
    }
}

//?????????IP??????
void SupplyWriter::on_lineEdit_14_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    Sleep(1500);
    try_connect_db();
}

//??????????????????
void SupplyWriter::on_lineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    Sleep(1500);
    try_connect_db();
}

//??????
void SupplyWriter::on_lineEdit_4_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    Sleep(1500);
    try_connect_db();
}

//?????????ODBC?????????
void SupplyWriter::on_lineEdit_5_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    Sleep(1500);
    try_connect_db();
}

void SupplyWriter::Update_FixtureStatus()
{
    if (working_mode == _AUTO_WRITE_MODE)
    {
        if (server_status == _SUCCESS_STATUS && odbc_status == _SUCCESS_STATUS)
        {
            ui->lineEdit_3->setEnabled(true);
            ui->lineEdit_3->setFocus();
        }
        else
        {
            ui->lineEdit_3->setEnabled(false);
        }
    }
    else
    {
        ui->lineEdit_3->setEnabled(true);
    }

    if (server_status == _FAILED_STATUS)
    {
        ui->label_2->setText("<p style=\"color:red;font-weight:bold\">???????????????</p>");
        ui->label_45->setText("<p style=\"color:red;font-size:45px;font-weight:bold\">\?\?</p>");
    }
}

void SupplyWriter::on_pushButton_clicked()
{
    //?????????????????????
    this->hide();

    //??????QSystemTrayIcon??????
    if (trayIcon == NULL)
    {
        trayIcon = new QSystemTrayIcon(this);
        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

        //????????????????????????icon
        QIcon icon = QIcon(":/images/stayicon.png");
        //???icon??????QSystemTrayIcon?????????
        trayIcon->setIcon(icon);

        //????????????????????????????????????????????????????????????????????????
        trayIcon->setToolTip(QString("???????????? ??????????????????"));
    }

    //??????????????????????????????
    trayIcon->show();
}

void SupplyWriter::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
    case QSystemTrayIcon::Trigger:
        //??????????????????
        break;

    case QSystemTrayIcon::DoubleClick:
        //??????????????????
        //??????????????????????????????
        this->show();
        trayIcon->hide();
        break;

    default:
        break;
    }
}

void SupplyWriter::play_mp3_sound(QString file)
{
    player->setMedia(QMediaContent(QUrl::fromLocalFile(file)));
    player->play();
}

void SupplyWriter::slotGetDBStatus(quint8 _odbc_status)
{
    if (working_mode == _AUTO_WRITE_MODE)
    {
        if (_odbc_status == _SUCCESS_STATUS && server_status == _SUCCESS_STATUS)
        {
            ui->lineEdit_3->setEnabled(true);
            ui->lineEdit_3->setFocus();
        }
        else
        {
            ui->lineEdit_3->setEnabled(false);
        }
    }
    else
    {
        ui->lineEdit_3->setEnabled(true);
    }

    if (odbc_status == _odbc_status)
        return;
    else
        odbc_status = _odbc_status;

    if (odbc_status == _FAILED_STATUS)
    {
        ui->label_13->setText(tr("<font style='color:red; font:bold;'>%1</font>").arg(QStringLiteral("???????????????")));
    }
    else if (odbc_status == _SUCCESS_STATUS)
    {
        ui->label_13->setText(tr("<font style='color:green; font:bold;'>%1</font>").arg(QStringLiteral("???????????????")));
    }
    else if (odbc_status == _INVALID_PARA)
    {
        ui->label_13->setText(tr("<font style='color:red; font:bold;'>%1</font>").arg(QStringLiteral("??????????????????")));
    }
}

void SupplyWriter::update_connect_fixture()
{
    if (checkIpValid(checkIPversion(ui->lineEdit_1->text()), ui->lineEdit_1->text()))
    {
        server_status = check_server_status();
    }
    else
    {
        server_status = _INVALID_PARA;
    }

    Update_FixtureStatus();
}

void SupplyWriter::on_radioButton_2_clicked()
{
//    qDebug() << "setting auto write mode" << working_mode;
    ui->lineEdit_14->setFocus();

    ui->QuerySqlButton->setEnabled(false);
    ui->DeleteSqlButton->setEnabled(false);

    if (working_mode == _AUTO_WRITE_MODE)
        return;
    else
        working_mode = _AUTO_WRITE_MODE;
}

void SupplyWriter::on_radioButton_clicked()
{
//    qDebug() << "setting manual read mode" << working_mode;

    ui->lineEdit_3->setEnabled(true);
    ui->lineEdit_3->setFocus();

    if (odbc_status == _SUCCESS_STATUS)
    {
        ui->QuerySqlButton->setEnabled(true);
        ui->DeleteSqlButton->setEnabled(true);
    }

    if (working_mode == _MANUAL_READ_MODE)
        return;
    else
        working_mode = _MANUAL_READ_MODE;
}
