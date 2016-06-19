#include <QString>
#include <QStringList>


class DataProcessor {
protected:
  int resultValue;
  QString errorMessage;
public:
  DataProcessor();
  ~DataProcessor();

  QString getErrorMessage() const;

  bool process(const QStringList& strValues);

  int getResult() const;
};
