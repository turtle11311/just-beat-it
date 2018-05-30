#include "histogramwidget.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QtWidgets>

qreal getPeakValue(const QAudioFormat& format)
{
    if (!format.isValid())
        return qreal(0);
    if (format.codec() != "audio/pcm")
        return qreal(0);
    switch (format.sampleType()) {
    case QAudioFormat::Unknown:
        break;
    case QAudioFormat::Float:
        if (format.sampleSize() != 32)
            return qreal(0);
        return qreal(1.00003);
    case QAudioFormat::SignedInt:
        if (format.sampleSize() == 32)
            return qreal(INT_MAX);
        if (format.sampleSize() == 16)
            return qreal(SHRT_MAX);
        if (format.sampleSize() == 8)
            return qreal(CHAR_MAX);
        break;
    case QAudioFormat::UnSignedInt:
        if (format.sampleSize() == 32)
            return qreal(UINT_MAX);
        if (format.sampleSize() == 16)
            return qreal(USHRT_MAX);
        if (format.sampleSize() == 8)
            return qreal(UCHAR_MAX);
        break;
    }
    return qreal(0);
}

template <class T>
static QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels)
{
    QVector<qreal> max_values;
    max_values.fill(0, channels);
    for (int i = 0; i < frames; ++i) {
        for (int j = 0; j < channels; ++j) {
            qreal value = qAbs(qreal(buffer[i * channels + j]));
            if (value > max_values.at(j))
                max_values.replace(j, value);
        }
    }
    return max_values;
}

QVector<qreal> getBufferLevels(const QAudioBuffer& buffer)
{
    QVector<qreal> values;
    if (!buffer.isValid())
        return values;
    if (!buffer.format().isValid() || buffer.format().byteOrder() != QAudioFormat::LittleEndian)
        return values;
    if (buffer.format().codec() != "audio/pcm")
        return values;
    int channelCount = buffer.format().channelCount();
    values.fill(0, channelCount);
    qreal peak_value = getPeakValue(buffer.format());
    if (qFuzzyCompare(peak_value, qreal(0)))
        return values;
    switch (buffer.format().sampleType()) {
    case QAudioFormat::Unknown:
    case QAudioFormat::UnSignedInt:
        if (buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<quint32>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<quint16>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<quint8>(), buffer.frameCount(), channelCount);
        for (int i = 0; i < values.size(); ++i)
            values[i] = qAbs(values.at(i) - peak_value / 2) / (peak_value / 2);
        break;
    case QAudioFormat::Float:
        if (buffer.format().sampleSize() == 32) {
            values = getBufferLevels(buffer.constData<float>(), buffer.frameCount(), channelCount);
            for (int i = 0; i < values.size(); ++i)
                values[i] /= peak_value;
        }
        break;
    case QAudioFormat::SignedInt:
        if (buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<qint32>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<qint16>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<qint8>(), buffer.frameCount(), channelCount);
        for (int i = 0; i < values.size(); ++i)
            values[i] /= peak_value;
        break;
    }
    return values;
}

QAudioLevel::QAudioLevel(QWidget *parent)
    : QWidget(parent)
{
    setMinimumWidth(3);
    setMaximumWidth(15);
}

void QAudioLevel::setLevel(qreal l)
{
    if (level != l) {
        level = l;
        update();
    }
}

void QAudioLevel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    qreal value = level * height();
    if(value != 0)
        painter.fillRect(0, ( height() - value ) / 2, width(), value, Qt::red);
}

HistogramWidget::HistogramWidget(QWidget *parent)
    : QWidget(parent)
{
    setLayout(new QHBoxLayout);
    qDeleteAll(audioLevels);
    audioLevels.clear();
    levelQueues.clear();
    for (int i = 0; i < numLevels; ++i) {
        QAudioLevel *level = new QAudioLevel(this);
        audioLevels.append(level);
        levelQueues.enqueue(0);
        layout()->addWidget(level);
    }
}

void HistogramWidget::processBuffer(const QAudioBuffer &buffer)
{
    QVector<qreal> levels = getBufferLevels(buffer);
    levelQueues.dequeue();
    levelQueues.enqueue(levels.at(0));
    for (int i = 0; i < numLevels; ++i)
        audioLevels.at(i)->setLevel(levelQueues.at(numLevels - i - 1));
}
