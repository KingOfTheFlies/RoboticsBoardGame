#pragma once

#include "AbstractModel.h"
#include "Field.h"
#include "Field.h"

class FieldCreate : public AbstractEvent {
public:
    FieldCreate() {};

    FieldCreate(std::string_view input_file);

    bool LoadFromFile(std::string_view input_file);

    void runEvent(std::list<AbstractObject*>& objects, TimeSpan time_span) override;

    Field* GetField() {
        return &field;
    }

protected:
    Field field;
};

