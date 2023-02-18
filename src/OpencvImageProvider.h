#ifndef CAT_CAM_OPENCVIMAGEPROVIDER_H
#define CAT_CAM_OPENCVIMAGEPROVIDER_H

#include <QImage>
#include <QObject>
#include <QQuickImageProvider>

namespace cat { namespace cam {

class OpencvImageProvider : public QQuickImageProvider
{
  Q_OBJECT
public:
  OpencvImageProvider(QObject* parent = nullptr);

  QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;

public slots:
  void updateImage(const QImage& image);

signals:
  void imageChanged();

private:
  QImage image;
};

} // end namespace cam
} // end namespace cat

#endif // CAT_CAM_OPENCVIMAGEPROVIDER_H
