#pragma once
#include <string>

#include "UniDxDefine.h"
#include "Property.h"

namespace UniDx {

// --------------------
// Object基底クラス
// --------------------
class Object
{
public:
    typedef ReadOnlyProperty<wstring>::Getter NameGetter;

    virtual ~Object() {}

    ReadOnlyProperty<wstring> name;

    Object(NameGetter nameGet) : name(nameGet) {}
};

} // namespace UniDx
