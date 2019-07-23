/****************************************************************************
** Copyright (c) 2019, Fougue Ltd. <http://www.fougue.pro>
** All rights reserved.
** See license at https://github.com/fougue/mayo/blob/master/LICENSE.txt
****************************************************************************/

#include "property_enumeration.h"

#include "options.h"

#include <cassert>
#include <QtCore/QCoreApplication>

namespace Mayo {

void Enumeration::map(Value eval, const QString& str)
{
    const Mapping mapping = { eval, str };
    m_vecMapping.emplace_back(std::move(mapping));
}

size_t Enumeration::size() const
{
    return m_vecMapping.size();
}

size_t Enumeration::index(Value eval) const
{
    return this->findCppSql(eval) - m_vecMapping.cbegin();
}

Enumeration::Value Enumeration::valueAt(size_t i) const
{
    return m_vecMapping.at(i).value;
}

Enumeration::Value Enumeration::value(const QString& str) const
{
    for (const Mapping& mapping : m_vecMapping) {
        if (mapping.string == str)
            return mapping.value;
    }
    assert(false);
    return -1;
}

const QString& Enumeration::string(Value eval) const
{
    auto it = this->findCppSql(eval);
    assert(it != m_vecMapping.cend());
    return it->string;
}

Enumeration::Mapping Enumeration::mapping(size_t i) const
{
    assert(i < m_vecMapping.size());
    return m_vecMapping.at(i);
}

Span<const Enumeration::Mapping> Enumeration::mappings() const
{
    return m_vecMapping;
}

std::vector<Enumeration::Mapping>::const_iterator
Enumeration::findCppSql(Value eval) const
{
    auto it = std::find_if(
                m_vecMapping.cbegin(),
                m_vecMapping.cend(),
                [=] (const Mapping& map) { return map.value == eval; } );
    assert(it != m_vecMapping.cend());
    return it;
}

PropertyEnumeration::PropertyEnumeration(
        PropertyOwner* owner,
        const QString& label,
        const Enumeration* enumeration)
    : Property(owner, label),
      m_enumeration(enumeration)
{
    assert(m_enumeration != nullptr);
    assert(m_enumeration->size() > 0);
    m_value = m_enumeration->valueAt(0);
}

const Enumeration& PropertyEnumeration::enumeration() const
{
    return *m_enumeration;
}

const QString& PropertyEnumeration::string() const
{
    return m_enumeration->string(m_value);
}

Enumeration::Value PropertyEnumeration::value() const
{
    return m_value;
}

Result<void> PropertyEnumeration::setValue(Enumeration::Value v)
{
    // TODO: check v is an enumerated value of m_enumeration
    return Property::setValueHelper(this, &m_value, v);
}

QVariant PropertyEnumeration::valueAsVariant() const
{
    return QVariant::fromValue(m_value);
}

Result<void> PropertyEnumeration::setValueFromVariant(const QVariant& value)
{
    return this->setValue(value.toInt());
}

const char* PropertyEnumeration::dynTypeName() const
{
    return PropertyEnumeration::TypeName;
}

const char PropertyEnumeration::TypeName[] = "Mayo::PropertyEnumeration";

const Enumeration &enum_Graphic3dNameOfMaterial()
{
    static Enumeration enumeration;
    if (enumeration.size() == 0) {
        enumeration.map(
                    Graphic3d_NOM_BRASS,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Brass"));
        enumeration.map(
                    Graphic3d_NOM_BRONZE,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Bronze"));
        enumeration.map(
                    Graphic3d_NOM_COPPER,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Copper"));
        enumeration.map(
                    Graphic3d_NOM_GOLD,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Gold"));
        enumeration.map(
                    Graphic3d_NOM_PEWTER,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Pewter"));
        enumeration.map(
                    Graphic3d_NOM_PLASTER,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Plaster"));
        enumeration.map(
                    Graphic3d_NOM_PLASTIC,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Plastic"));
        enumeration.map(
                    Graphic3d_NOM_SILVER,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Silver"));
        enumeration.map(
                    Graphic3d_NOM_STEEL,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Steel"));
        enumeration.map(
                    Graphic3d_NOM_STONE,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Stone"));
        enumeration.map(
                    Graphic3d_NOM_SHINY_PLASTIC,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Shiny plastic"));
        enumeration.map(
                    Graphic3d_NOM_SATIN,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Satin"));
        enumeration.map(
                    Graphic3d_NOM_METALIZED,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Metalized"));
        enumeration.map(
                    Graphic3d_NOM_NEON_GNC,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Neon gnc"));
        enumeration.map(
                    Graphic3d_NOM_CHROME,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Chrome"));
        enumeration.map(
                    Graphic3d_NOM_ALUMINIUM,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Aluminium"));
        enumeration.map(
                    Graphic3d_NOM_OBSIDIAN,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Obsidian"));
        enumeration.map(
                    Graphic3d_NOM_NEON_PHC,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Neon phc"));
        enumeration.map(
                    Graphic3d_NOM_JADE,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Jade"));
        enumeration.map(
                    Graphic3d_NOM_DEFAULT,
                    QCoreApplication::translate("Mayo::EnumGpxMaterial", "Default"));
    }
    return enumeration;
}

const Enumeration &enum_AspectHatchStyle()
{
    static Enumeration enumeration;
    if (enumeration.size() == 0) {
        enumeration.map(
                    Aspect_HS_SOLID,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Solid"));
        enumeration.map(
                    Aspect_HS_HORIZONTAL,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Horizontal"));
        enumeration.map(
                    Aspect_HS_HORIZONTAL_WIDE,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Horizontal sparse"));
        enumeration.map(
                    Aspect_HS_VERTICAL,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Vertical"));
        enumeration.map(
                    Aspect_HS_VERTICAL_WIDE,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Vertical sparse"));
        enumeration.map(
                    Aspect_HS_DIAGONAL_45,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Diagonal_45"));
        enumeration.map(
                    Aspect_HS_DIAGONAL_45_WIDE,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Diagonal_45 sparse"));
        enumeration.map(
                    Aspect_HS_DIAGONAL_135,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Diagonal_135"));
        enumeration.map(
                    Aspect_HS_DIAGONAL_135_WIDE,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Diagonal_135 sparse"));
        enumeration.map(
                    Aspect_HS_GRID,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Grid"));
        enumeration.map(
                    Aspect_HS_GRID_WIDE,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Grid sparse"));
        enumeration.map(
                    Aspect_HS_GRID_DIAGONAL,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Grid diagonal"));
        enumeration.map(
                    Aspect_HS_GRID_DIAGONAL_WIDE,
                    QCoreApplication::translate("Mayo::EnumHatchStyle", "Grid diagonal sparse"));
    }
    return enumeration;
}

} // namespace Mayo
