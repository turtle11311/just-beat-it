#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QAudioBuffer>
#include <QQueue>
#include <QWidget>

class QAudioLevel : public QWidget
{
    Q_OBJECT
public:
    explicit QAudioLevel(QWidget *parent = nullptr);
    void setLevel(qreal l);
protected:
    void paintEvent(QPaintEvent *event);
private:
    qreal level = 0;
};

class HistogramWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HistogramWidget(QWidget *parent = nullptr);
public slots:
    void processBuffer(const QAudioBuffer &buffer);
private:
    QVector<QAudioLevel *> audioLevels;
    QQueue<qreal> levelQueues;
    int numLevels = 15;
};

#endif // HISTOGRAMWIDGET_H
