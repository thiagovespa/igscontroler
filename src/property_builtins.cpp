/****************************************************************************
** Copyright (c) 2019, Fougue Ltd. <http://www.fougue.pro>
** All rights reserved.
** See license at https://github.com/fougue/mayo/blob/master/LICENSE.txt
****************************************************************************/

#include "property_builtins.h"

namespace Mayo {

const char *BasePropertyQuantity::dynTypeName() const
{
    return BasePropertyQuantity::TypeName;
}

BasePropertyQuantity::BasePropertyQuantity(PropertyOwner *owner, const QString &label)
    : Property(owner, label)
{
}

template<> const char PropertyBool::TypeName[] = "Mayo::PropertyBool";
template<> const char GenericProperty<int>/*PropertyInt*/::TypeName[] = "Mayo::PropertyInt";
template<> const char GenericProperty<double>/*PropertyDouble*/::TypeName[] = "Mayo::PropertyDouble";
template<> const char PropertyQByteArray::TypeName[] = "Mayo::PropertyQByteArray";
template<> const char PropertyQString::TypeName[] = "Mayo::PropertyQString";
template<> const char PropertyQDateTime::TypeName[] = "Mayo::PropertyQDateTime";
template<> const char PropertyOccColor::TypeName[] = "Mayo::PropertyOccColor";
template<> const char PropertyOccPnt::TypeName[] = "Mayo::PropertyOccPnt";
template<> const char PropertyOccTrsf::TypeName[] = "Mayo::PropertyOccTrsf";

const char BasePropertyQuantity::TypeName[] = "Mayo::BasePropertyQuantity";

} // namespace Mayo
