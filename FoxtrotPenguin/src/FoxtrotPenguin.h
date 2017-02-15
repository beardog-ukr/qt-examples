#ifndef __FoxtrotPenguin__
#define __FoxtrotPenguin__

#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QStringList>
class QSslError;

class FoxtrotPenguin : public QObject
{
  Q_OBJECT
public:
  FoxtrotPenguin(QObject *parent = 0);
  virtual ~FoxtrotPenguin();

  bool startAction(const QString& actionOption);

  void startSimpleGet();
  void startLongGet() ;
  void startSimpleParamGet() ;
  void startParamGet() ;
  void startPostForm() ;

public slots:
  void processSimpeGetFinished(QNetworkReply*);

  void processLongGetReadyRead();
  void processLongGetFinished();

  void processSimpleParamGetFinished(QNetworkReply*) ;
  void processParamGetFinished(QNetworkReply*) ;

  void processPostFormFinished(QNetworkReply*) ;

  #ifndef QT_NO_SSL
  void sslErrors(QNetworkReply*,const QList<QSslError> &errors);
  #endif

protected:

  QNetworkAccessManager* nam ;
  QNetworkReply* currentReply;
  QByteArray receivedData;

  void writeFile(const QString fileName, const QByteArray& ba) ;

};

#endif
