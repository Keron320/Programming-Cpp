#pragma once
class cMouse
{
public:
	bool            MoveTo(const cVector2 &toPos) {
		pos = toPos;
		return 1;
	}
	cVector2        GetPos() { return pos; }
	bool            FoundCheese() { return hasFoundCheese; }
	void            Cheese() { hasFoundCheese = true; }
private:
	cVector2        pos{ 0, 0 };
	bool            hasFoundCheese{ false };
};
