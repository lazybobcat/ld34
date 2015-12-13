#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <string>
#include <cstring>

#include <GUI/widget.hpp>
#include <resources/resourceholder.hpp>
#include <resources/resourceidentifiers.hpp>

namespace GUI
{

class LineEdit: public Widget
{
public:
    typedef std::shared_ptr<LineEdit> Ptr;
    typedef std::function<void()>   Callback;

public:
    LineEdit(FontHolder& fonts, const std::string& text = "");

    void            setOnLostFocus(Callback callback);
    virtual bool    isSelectable() const;
    virtual void    select();
    virtual void    deselect();
    virtual void    activate();
    virtual void    deactivate();
    virtual void    handleEvent(const sf::Event &event);

    void            setText(const std::string& text);
    void            setCharacterSize(unsigned int size);
    void            setSize(sf::Vector2i size);
    void            setSize(unsigned int x, unsigned int y);
    void            setColor(const sf::Color& color);

    std::string     getString() const;

protected:
    virtual void    draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    void            moveCursorLeft();
    void            moveCursorRight();
    void            insertCharacter(char c);
    void            backspace();
    void            adaptTextToBox();

private:
    Callback            mCallback;
    std::string         mString;
    sf::Text            mText;
    sf::RectangleShape  mShape;
    std::size_t         mCursorPosition;
};

}

#endif // LINEEDIT_H
