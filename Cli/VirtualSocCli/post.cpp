#include "post.h"
#include <QtDebug>

Post::Post(QString post){
    QStringList postDetails = post.split(QLatin1Char('~'));

    PostId=postDetails[0].toInt();
    PostVisibility=postDetails[1];
    UserId=postDetails[2].toInt();
    PostDate=postDetails[3];
    PostText=postDetails[4];
    Likes=postDetails[5].toInt();
    PostTitle=postDetails[6];
}
