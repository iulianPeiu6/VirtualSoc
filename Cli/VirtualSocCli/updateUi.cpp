#include "updateUi.h"

void updateUser(Ui::Home *ui, User* user){
    ui->current_username_info_label=user->Username;
}
