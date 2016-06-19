#include <QString>
#include <QStringList>

class FileLoader {
protected:
  QString errorMessage;
  QStringList lines;
public:
  FileLoader();
  ~FileLoader();

  QString getErrorMessage() const;

  bool loadFile(const QString fileName);

  QStringList getResult(const bool clear = true) ;
};
