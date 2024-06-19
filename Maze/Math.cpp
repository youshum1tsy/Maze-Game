#include "Math.h"
bool DidRectCollision(sf::FloatRect rect1, sf::FloatRect rect2) {
	bool result;

	__asm {
		push eax;
		push ebx;
		push ecx;
		push edx;

		fld rect1.left;
		fadd rect1.width;
		fcomp rect2.left;
		fnstsw ax;
		sahf;
		jbe no_collision;

		fld rect2.left;
		fadd rect2.width;
		fcomp rect1.left;
		fnstsw ax;
		sahf;
		jbe no_collision;

		fld rect1.top;
		fadd rect1.height;
		fcomp rect2.top;
		fnstsw ax;
		sahf;
		jbe no_collision;

		fld rect2.top;
		fadd rect2.height;
		fcomp rect1.top;
		fnstsw ax;
		sahf;
		jbe no_collision;

		mov result, 1;
		jmp end;

	no_collision:
		mov result, 0;

	end:
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
	}
	return result;
}