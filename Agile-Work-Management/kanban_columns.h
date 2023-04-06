#ifndef KANBAN_COLUMNS_H
#define KANBAN_COLUMNS_H

#include <string>

class KanbanColumn {
private:
    int id_;
    std::string name_;
    int board_id_;
    int position_;

public:
    KanbanColumn() : id_(0), board_id_(0), position_(0) {}

    KanbanColumn(int id, const std::string& name, int board_id, int position)
        : id_(id), name_(name), board_id_(board_id), position_(position) {}

    int getId() const { return id_; }
    void setId(int id) { id_ = id; }

    const std::string& getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }

    int getBoardId() const { return board_id_; }
    void setBoardId(int board_id) { board_id_ = board_id; }

    int getPosition() const { return position_; }
    void setPosition(int position) { position_ = position; }
};

#endif
