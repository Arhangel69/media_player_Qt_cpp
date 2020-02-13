#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_play_clicked();
    void on_btn_pause_clicked();
    void on_btn_stop_clicked();
    void on_btn_loop_clicked();

    void on_btn_choose_clicked();

    void on_btn_add_clicked();
    void on_btn_drop_clicked();

    void set_progress_bar_lenght(double value);
    void set_progress_bar();
    void set_volume();

    void index_changed();

    void on_btn_exit_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer player;
    QMediaPlaylist playlist;
    bool flag_empty_playlist = true;
    bool flag_loop_playlist = false;
};

#endif // MAINWINDOW_HPP
