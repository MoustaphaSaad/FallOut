#ifndef VISUALCOMPOSER_H
#define VISUALCOMPOSER_H
namespace Fallout{
class visualComposer{
public:
	bool castShadow;
	bool receiveShadow;
	visualComposer(){
		castShadow = false;
		receiveShadow = true;
	}
};
}
#endif