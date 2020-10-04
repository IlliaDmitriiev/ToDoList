//
// Created by ilya on 04.10.2020.
//

#ifndef TODOLIST_MODELPERSISTER_H
#define TODOLIST_MODELPERSISTER_H

#include "Model.pb.h"
#include "Persister.h"
#include "Core/model/DataHolder.h"
#include "fstream"

/*
 *  File persister
 *
 *  @author: Ilya Dmitriev
 */
class ModelPersister: public Persister {
public:
    ModelPersister(DataInterface& dataHolder,
                   std::fstream& file)
                  :
    model_(dataHolder),
    file_(std::move(file))
    {

    }

public:
    bool save() override;
    bool load() override;

private:
    bool saveSubtasks(const ModelTaskDTO&, TaskEntity* );
    bool loadSubtasks(TaskID, const TaskEntity&);

private:
    std::fstream file_;
    DataInterface& model_;
};


#endif //TODOLIST_MODELPERSISTER_H
