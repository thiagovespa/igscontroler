/****************************************************************************
** Copyright (c) 2019, Fougue Ltd. <http://www.fougue.pro>
** All rights reserved.
** See license at https://github.com/fougue/mayo/blob/master/LICENSE.txt
****************************************************************************/

#pragma once

#include <AIS_InteractiveObject.hxx>
#include <Aspect_TypeOfDisplayText.hxx>
#include <Aspect_TypeOfStyleText.hxx>
#include <gp_Pnt.hxx>
#include <Graphic3d_AspectText3d.hxx>
#include <Prs3d_Presentation.hxx>
#include <Prs3d_Projector.hxx>
#include <Prs3d_TextAspect.hxx>
#include <PrsMgr_PresentationManager3d.hxx>
#include <SelectMgr_Selection.hxx>
#include <Quantity_Color.hxx>
#include <TCollection_ExtendedString.hxx>

namespace Mayo {

class AIS_Text : public AIS_InteractiveObject {
public:
    AIS_Text() = default;
    AIS_Text(const TCollection_ExtendedString& text, const gp_Pnt& pos);

    Handle_Prs3d_TextAspect presentationTextAspect(unsigned i = 0) const;
    Handle_Graphic3d_AspectText3d graphicTextAspect(unsigned i = 0) const;

    void setDefaultColor(const Quantity_Color& c);
    void setDefaultFont(const char* fontName);
    void setDefaultTextBackgroundColor(const Quantity_Color& c);
    void setDefaultTextDisplayMode(Aspect_TypeOfDisplayText mode);
    void setDefaultTextStyle(Aspect_TypeOfStyleText style);

    gp_Pnt position(unsigned i = 0) const;
    void setPosition(const gp_Pnt& pos, unsigned i = 0);

    TCollection_ExtendedString text(unsigned i = 0) const;
    void setText(const TCollection_ExtendedString& v, unsigned i = 0);
    bool isValidTextIndex(unsigned i) const;

    void setTextBackgroundColor(const Quantity_Color& color, unsigned i = 0);
    void setTextDisplayMode(Aspect_TypeOfDisplayText mode, unsigned i = 0);
    void setTextStyle(Aspect_TypeOfStyleText style, unsigned i = 0);

    unsigned textCount() const;
    void addText(const TCollection_ExtendedString& text, const gp_Pnt& pos);

    void ComputeSelection(
            const opencascade::handle<SelectMgr_Selection>& sel,
            const int mode) override;

protected:
    void Compute(
            const opencascade::handle<PrsMgr_PresentationManager3d>& pm,
            const opencascade::handle<Prs3d_Presentation>& pres,
            const int mode) override;
    void Compute(
            const opencascade::handle<Prs3d_Projector>& proj,
            const opencascade::handle<Prs3d_Presentation>& pres) override;

private:
    struct TextProperties {
        TextProperties();
        bool operator==(const TextProperties& other) const;
        const char* m_font = nullptr;
        gp_Pnt m_position;
        TCollection_ExtendedString m_text;
        Handle_Prs3d_TextAspect m_aspect;
    };

    const char* m_defaultFont = "Courrier";
    Quantity_Color m_defaultColor = Quantity_NOC_YELLOW;
    Quantity_Color m_defaultTextBackgroundColor = Quantity_NOC_GREEN;
    Aspect_TypeOfDisplayText m_defaultTextDisplayMode = Aspect_TODT_NORMAL;
    Aspect_TypeOfStyleText m_defaultTextStyle = Aspect_TOST_NORMAL;
    std::vector<TextProperties> m_textProps;
};

} // namespace Mayo
