#include "medpl_pr/mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_exit, &QPushButton::clicked, this, &MainWindow::on_btn_exit_clicked);
    connect(ui->sld_volume, &QSlider::sliderMoved, this, &MainWindow::set_volume);
    connect(ui->btn_addmusic, &QPushButton::clicked, this, &MainWindow::on_btn_add_clicked);
    connect(ui->btn_dropmusic, &QPushButton::clicked, this, &MainWindow::on_btn_drop_clicked);
    connect(ui->btn_next, &QPushButton::clicked, &playlist, &QMediaPlaylist::next);
    connect(ui->btn_previous, &QPushButton::clicked, &playlist, &QMediaPlaylist::previous);
    //connect(ui->btn_loop, &QPushButton::clicked, this, &MainWindow::on_btn_loop_clicked);

    connect(&player, &QMediaPlayer::durationChanged, ui->progressBar, &QProgressBar::setMaximum);
    connect(&player, &QMediaPlayer::positionChanged, this, &MainWindow::set_progress_bar);
    connect(&playlist, &QMediaPlaylist::currentIndexChanged, this, &MainWindow::index_changed);

    ui->btn_pause->hide();
    ui->lbl_nothing_to_play->hide();
    ui->lbl_volume_value->setText(QString::number(ui->sld_volume->value()));
    ui->txted_playlist->setReadOnly(true);

    playlist.setPlaybackMode(QMediaPlaylist::Sequential);
    player.setVolume(ui->sld_volume->value());
    player.setPlaylist(&playlist);
}

void MainWindow::index_changed()
{
    if ((playlist.currentIndex())==-1)
    {
        ui->btn_pause->hide();
        ui->btn_play->show();
        ui->lbl_current_index->setText("");
        ui->path_wave->setPlainText("Playlist ended");
    }
    else
    {
        ui->lbl_current_index->setText(QString::number(playlist.currentIndex()+1));
        ui->path_wave->setPlainText(QUrl(playlist.currentMedia().canonicalUrl()).fileName());
    }
}

void MainWindow::set_volume()
{
    ui->lbl_volume_value->setText(QString::number(ui->sld_volume->value()));
    player.setVolume(ui->sld_volume->value());
}

void MainWindow::on_btn_choose_clicked()
{
    playlist.clear();
    ui->txted_playlist->clear();
    QFileDialog dialog_open_file(this);
    dialog_open_file.setNameFilter(tr("Audio Files (*.wav *.mp3)"));
    QString path_music_file = dialog_open_file.getOpenFileName();
    if (!(path_music_file.isEmpty()))
    {
        playlist.addMedia(QUrl::fromLocalFile(path_music_file));
        ui->path_wave->setPlainText(QDir(path_music_file).dirName());
        ui->lbl_nothing_to_play->hide();
    }
}

void MainWindow::on_btn_play_clicked()
{
    if ((playlist.isEmpty()))
    {
        ui->lbl_nothing_to_play->show();
    }
    else
    {
        ui->lbl_nothing_to_play->hide();
        player.play();
        ui->path_wave->setPlainText(QUrl(playlist.currentMedia().canonicalUrl()).fileName());
        ui->btn_play->hide();
        ui->btn_pause->show();
    }
}

void MainWindow::on_btn_pause_clicked()
{
    player.pause();
    ui->path_wave->setPlainText("Paused");
    ui->btn_play->show();
    ui->btn_pause->hide();
}

void MainWindow::on_btn_stop_clicked()
{
    player.stop();
    ui->btn_play->show();
    ui->btn_pause->hide();
    ui->path_wave->setPlainText("Stopped");
}

void MainWindow::on_btn_add_clicked()
{
    QFileDialog dialog_open_file(this);
    dialog_open_file.setNameFilter(tr("Audio Files (*.wav *.mp3)"));
    QString path_file_of_playlist = dialog_open_file.getOpenFileName();
    if (!(path_file_of_playlist.isEmpty()))
    {
        playlist.addMedia(QUrl::fromLocalFile(path_file_of_playlist));
        if (flag_empty_playlist)
        {
            ui->txted_playlist->setPlainText(QString::number(playlist.mediaCount())+". "+QDir(path_file_of_playlist).dirName()+"\n");
            flag_empty_playlist = false;
            ui->lbl_current_index->setText(QString::number(playlist.nextIndex()+1));
            playlist.setCurrentIndex(playlist.nextIndex());
        }
        else
        {
            ui->txted_playlist->insertPlainText(QString::number(playlist.mediaCount())+". "+QDir(path_file_of_playlist).dirName()+"\n");
        }
    }
}
void MainWindow::on_btn_drop_clicked()
{
    if (!(playlist.isEmpty()))
    {
        ui->txted_playlist->undo();
        if ((playlist.mediaCount())!=1)
        {
            playlist.removeMedia(playlist.mediaCount()-1);
        }
        else playlist.removeMedia(playlist.currentIndex());
        ui->path_wave->setPlainText(QUrl(playlist.currentMedia().canonicalUrl()).fileName());
    }
    if (playlist.isEmpty())
    {
        ui->txted_playlist->clear();
        ui->txted_playlist->setPlainText("Playlist is totally Empty!\n");
        ui->path_wave->setPlainText("Playlist is totally Empty!");
        ui->lbl_current_index->setText("");
        ui->btn_play->show();
        ui->btn_pause->hide();
        flag_empty_playlist = true;
    }
}

void MainWindow::on_btn_exit_clicked()
{
    this->close();
}

void MainWindow::on_btn_loop_clicked()
{
    if (flag_loop_playlist)
    {
        ui->btn_loop->setStyleSheet("Default;");
        playlist.setPlaybackMode(QMediaPlaylist::Sequential);
        flag_loop_playlist = false;
    }
    else if (!flag_loop_playlist)
    {
        ui->btn_loop->setStyleSheet(
                    "background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));"
                    "color: rgb(255, 0, 0);");
        playlist.setPlaybackMode(QMediaPlaylist::Loop);
        flag_loop_playlist = true;
    }
}

void MainWindow::set_progress_bar_lenght(double value)
{
    value/=1000;
    ui->progressBar->setMaximum(value);
}

void MainWindow::set_progress_bar()
{
    double value = player.position();
    ui->progressBar->setValue(value);
}

MainWindow::~MainWindow()
{
    delete ui;
}
