//
// Created by A on 05/06/2024.
//
#include <QMessageBox>
#include <QFormLayout>

#include "GUI.h"
void GUI::init_gui() {
    QFormLayout *layout= new QFormLayout{};
    main = new QHBoxLayout;
    right_side = new QVBoxLayout;
    mesaj = new QLabel("Choose a number between 1 and 5 and press NewGame");
    status = new QLabel;
    movess = new QLabel("Remaining moves: 30");
    reguli = new QLabel("Boat dimensions:\n1 boat with 2 cells\n1 boat with 3 cells\n1 boat with 4 cells");
    attack= new QPushButton("Attack");
    new_game = new QPushButton("New Game");
    config = new QLineEdit;
    table_view = new QTableView;
    table_model = new BattleshipTableModel(board);
    table_view->setModel(table_model);
    table_view->resizeColumnsToContents();
    table_view->resizeRowsToContents();

    layout->addRow("Choose a game (number between 1 and 5):",config);
    setLayout(main);
    main->addWidget(table_view);
    right_side->addWidget(mesaj);
    right_side->addWidget(reguli);
    right_side->addWidget(movess);
    right_side->addWidget(status);
    right_side->addWidget(attack);
    right_side->addLayout(layout);
    right_side->addWidget(new_game);
    main->addLayout(right_side);

}

void GUI::connect(){
    QObject::connect(attack, &QPushButton::clicked, [&](){
        QModelIndexList indexes = table_view->selectionModel()->selectedIndexes();
        if(indexes.isEmpty()){
            QMessageBox::warning( nullptr, "oops!","select a cell to attack.");
        }
        else{
            QModelIndex index =table_view->selectionModel()->selectedIndexes()[0];
            try{
                board.attack_coordinates(index.row(),index.column());
            }
            catch (BoardException &ex){
                QMessageBox::warning(nullptr,"oops!", "point already attacked!");
            }
        }
        reload_table();
    });
    QObject::connect(new_game,&QPushButton::clicked, [&](){
        int nr = config->text().toInt();
        if(nr<1 || nr>5)
        {
            QMessageBox::warning(nullptr, "oops!","Choose a number between 1 and 5");
        }
        else{
            board= Board(10,nr);
            reload_table();
        }
    });
}

void GUI::reload_table() {
    string msj="Remaining moves: "+std::to_string(board.get_moves());
    movess->setText(QString::fromStdString(msj));
    if(board.get_status()==0)
    {
        status->setText(QString::fromStdString("In progress..."));
    }
    else if(board.get_status()==1){
        status->setText(QString::fromStdString("Game lost :("));
        QMessageBox::information(nullptr,"Oh well..","You lost. Try one more time!");
    }
    else {
        status->setText(QString::fromStdString("Game won!! :)"));
        QMessageBox::information(nullptr,"Congrats!","You won!! :)");
    }
    table_model->update();
}