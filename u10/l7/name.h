#ifndef THEDILLETANTE_NAME
#define THEDILLETANTE_NAME

class Name
{
public:
	Name(const char* n);
private:
	const char* s;
};

inline Name::Name(const char* n) : s(n) {}

#endif // THEDILLETANTE_NAME