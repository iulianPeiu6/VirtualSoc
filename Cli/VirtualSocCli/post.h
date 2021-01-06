#ifndef POST_H
#define POST_H
#include <QString>
#include <QStringList>

class Post
{
public:
    Post(QString );
    int PostId;
    QString PostVisibility;
    int UserId;
    QString PostDate;
    QString PostText;
    int Likes;
    QString PostTitle;
};

#endif // POST_H
