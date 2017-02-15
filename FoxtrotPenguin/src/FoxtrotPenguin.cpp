#include "FoxtrotPenguin.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QSslError>
#include <QUrl>
#include <QUrlQuery>


// === =======================================================================
// === =======================================================================

FoxtrotPenguin::FoxtrotPenguin(QObject* parent)
             :QObject(parent){
   nam =0;
   currentReply=0;//
}

// === =======================================================================

FoxtrotPenguin::~FoxtrotPenguin() {
  //
}

// === =======================================================================

bool FoxtrotPenguin::startAction(const QString& actionOption) {
  qDebug() << "Starting" << actionOption;
  //
  //writeFile(".\\fff.txt", QString("try 01").toUtf8());
  if (actionOption=="sg") {
    startSimpleGet();
  }
  else if (actionOption=="lg") {
    startLongGet();
  }
  else   if (actionOption=="spg") {
    startSimpleParamGet();
  }
  else if (actionOption=="pg") {
    startParamGet();
  }
  else if (actionOption=="pf") {
    startPostForm();
  }
  else {
    qDebug() << "Unknown option code";
    return false;
  }

  return true;
}

// ============================================================================

void FoxtrotPenguin::writeFile(const QString fileName, const QByteArray& ba) {
  QFile data(fileName);
  if ( !data.open(QFile::WriteOnly|QFile::Truncate)) {
    qDebug() <<  "Problem opening file ("<< fileName << ")";
    return;
  }

  data.write(ba);
  data.close();
}


// === =======================================================================

void FoxtrotPenguin::startSimpleGet() {
  nam = new QNetworkAccessManager(this);

  connect(nam, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(processSimpeGetFinished(QNetworkReply*)));

          #ifndef QT_NO_SSL
              qDebug() << "connecting ssl errors slot";
              connect(nam, SIGNAL(sslErrors(QNetworkReply*,const QList<QSslError>&)),
                      this, SLOT(sslErrors(QNetworkReply*,const QList<QSslError> &)));
          #endif

  nam->get(QNetworkRequest(QUrl("http://doc.qt.io/")));
}

// === =======================================================================

void FoxtrotPenguin::processSimpeGetFinished(QNetworkReply *reply) {
  if (reply->error() != QNetworkReply::NoError) {
    qDebug() << "Got some error " << reply->error();
    QCoreApplication::exit(1);
  }

  const int resultCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  qDebug() << "Received code " << resultCode;
  if (resultCode != 200) {
    QCoreApplication::exit(1);
  }

  writeFile(".\\simpelGetResult.html", reply->readAll());
  QCoreApplication::exit(0);
}

// === =======================================================================

void FoxtrotPenguin::startLongGet() {
  nam = new QNetworkAccessManager(this);

  currentReply = nam->get(QNetworkRequest(QUrl("http://doc.qt.io/")));

  connect(currentReply, SIGNAL(finished()), this, SLOT(processLongGetFinished()));
  connect(currentReply, SIGNAL(readyRead()), this, SLOT(processLongGetReadyRead()));
}

// === =======================================================================

void FoxtrotPenguin::processLongGetReadyRead() {
  qDebug() << "FoxtrotPenguin::processLongGetReadyRead " << "here";

  if (currentReply) {
    receivedData.append( currentReply->readAll() ) ;
  }
}

// === =======================================================================

void FoxtrotPenguin::processLongGetFinished() {
  if (!currentReply) {
    return;
  }

  if (currentReply->error() != QNetworkReply::NoError) {
    qDebug() << "Got some error " << currentReply->error();
    QCoreApplication::exit(1);
  }

  const int resultCode = currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  qDebug() << "Received code " << resultCode;
  if (resultCode != 200) {
    QCoreApplication::exit(1);
  }

  writeFile(".\\longGetResult.html", receivedData);

  currentReply->deleteLater();
  //finally
  QCoreApplication::exit(0);
}


// === =======================================================================

void FoxtrotPenguin::startSimpleParamGet() {
  nam = new QNetworkAccessManager(this);

  connect(nam, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(processSimpleParamGetFinished(QNetworkReply*)));

  nam->get(QNetworkRequest(QUrl("http://w1.c1.rada.gov.ua/pls/radan_gs09/ns_golos?g_id=9711")));
}

// === =======================================================================

void FoxtrotPenguin::processSimpleParamGetFinished(QNetworkReply *reply) {
  if (reply->error() != QNetworkReply::NoError) {
    qDebug() << "Got some error " << reply->error();
    QCoreApplication::exit(1);
  }

  const int resultCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  qDebug() << "Received code " << resultCode;
  if (resultCode != 200) {
    QCoreApplication::exit(1);
  }

  writeFile(".\\spGetResult.html", reply->readAll());
  QCoreApplication::exit(0);
}

// === =======================================================================

void FoxtrotPenguin::startParamGet() {
  nam = new QNetworkAccessManager(this);

  connect(nam, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(processParamGetFinished(QNetworkReply*)));

  const QString endpoint = "https://validator.w3.org/nu/" ;

  QUrl url(endpoint);

  QUrlQuery query ;
  query.addQueryItem("doc", "http://rada.gov.ua/");

  url.setQuery(query);
  qDebug() <<  "url is " << url.toString();

  QNetworkRequest req( url ) ;

  nam->get( req );
}

// === =======================================================================

void FoxtrotPenguin::processParamGetFinished(QNetworkReply *reply) {
  if (reply->error() != QNetworkReply::NoError) {
    qDebug() << "Got some error " << reply->error();
    QCoreApplication::exit(1);
  }

  const int resultCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  qDebug() << "Received code " << resultCode;
  if (resultCode != 200) {
    QCoreApplication::exit(1);
  }

  writeFile(".\\paramGetResult.html", reply->readAll());
  QCoreApplication::exit(0);
}

// === =======================================================================

void FoxtrotPenguin::startPostForm() {
  nam = new QNetworkAccessManager(this);

  connect(nam, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(processPostFormFinished(QNetworkReply*)));

  const QString endpoint = "http://www.apcourtkiev.gov.ua/CourtPortal.WebSite/Home/GraficZasidan";
  QUrl url(endpoint);

  QUrlQuery query ;
  query.addQueryItem("case_number", "");
  query.addQueryItem("session_date", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
  query.addQueryItem("main_judge", "");
  query.addQueryItem("litigant", "");
  query.addQueryItem("doc_class", "");
  query.addQueryItem("Search", "Шукати");

  QString qs = query.query(QUrl::FullyEncoded) ;
  qs.replace("+", "%2B");

  QByteArray qsba = qs.toUtf8();

  QNetworkRequest nrq(url);
  nrq.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
  nrq.setHeader(QNetworkRequest::ContentLengthHeader, qsba.count());

//          nrq.setRawHeader(QString("User-Agent").toUtf8(),
//                        QString("Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:28.0) Gecko/20100101 Firefox/28.0").toUtf8());
//          nrq.setRawHeader("Accept-Encoding","gzip, deflate");
  nam->post( nrq, qsba);
}

// === =======================================================================

void FoxtrotPenguin::processPostFormFinished(QNetworkReply *reply) {
  if (reply->error() != QNetworkReply::NoError) {
    qDebug() << "Got some error " << reply->error();
    QCoreApplication::exit(1);
  }

  const int resultCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  qDebug() << "Received code " << resultCode;
  if (resultCode != 200) {
    QCoreApplication::exit(1);
  }

  writeFile(".\\postFormResult.html", reply->readAll());
  QCoreApplication::exit(0);
}

// === =======================================================================

#ifndef QT_NO_SSL
void FoxtrotPenguin::sslErrors(QNetworkReply*,const QList<QSslError> &errors)
{
    QString errorString;
    foreach (const QSslError &error, errors) {
        if (!errorString.isEmpty())
            errorString += '\n';
        errorString += error.errorString();
    }

    qDebug() << "SSL Errors" ;
    qDebug() << "One or more SSL errors has occurred: " << errorString;
}
#endif

// === =======================================================================
