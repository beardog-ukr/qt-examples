#include <QString>
#include <QStringList>

class FileProcessor {

friend class TestFileProcessor;

public:
  FileProcessor();
  ~FileProcessor();

  QString getErrorMessage() const;
  int getResult() const;

  bool loadFile(const QString fileName);

protected:
  bool processData(const QStringList& rawData);
  QString errorMessage;

  int resultValue;
};
