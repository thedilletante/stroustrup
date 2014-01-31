#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <fstream>
#include <vector>

/* program
**/
// the programm

enum Token_value {
	PREPROC_DIRECTIVE = '#', WORD,
	COMMENT = '/', STRING_LITERAL = '"', CHAR = '\'',
	SEPARATOR = ';', EOL = '\n',
	NUMBER,	CONTROL, END, SPACE = ' '
};

std::istream *input;
Token_value curr_tok = END;
std::string value;

void setValue(bool isString = true) {
	char ch;
	if (isString)
		while(input->get(ch) && (isalnum(ch) || ch == '_')) value.push_back(ch);
	else {
		while(input->get(ch) && (isdigit(ch))) value.push_back(ch);
	}
	input->putback(ch);
}

Token_value processComment() {
	char ch;
	if (input->get(ch)) {
		switch(ch) {
			case '*': {
				char last = '\0';
				while(input->get(ch)) {
					if (last == '*') {
						if (ch == COMMENT)
							break;
						value.push_back(last);
					}
					if (ch != '*')
						value.push_back(ch);
					last = ch;
				}
				if (!ch) return END;
				}
				return COMMENT;
			case '/': {
				bool ignore = false;
				while(input->get(ch)) {
					if (ignore) ignore = false;
					else if (ch == EOL) break;
					if (ch == '\\') ignore = true;
					else value.push_back(ch);
				}
				}
				return COMMENT;
			default:
				input->putback(ch);
				return CONTROL;
		}
		return COMMENT;
	}
	return COMMENT;
}

Token_value processLiteral(Token_value type) {
	bool ignore = false;
	char ch;
	while(input->get(ch)) {
		if (ignore) {
			ignore = false;
			value.push_back(ch);
			continue;
		}
		switch(ch) {
			case STRING_LITERAL: case CHAR:
				if (type == ch) return type;
				else value.push_back(ch);
				break;
			case '\\' : ignore = true; break;
			default : value.push_back(ch); break;
		}
	}
	return type;
}

Token_value processDirective() {
	char ch;
	bool ignore = false;
	while(input->get(ch)) {
		if (ignore) ignore = false;
		else if (ch == EOL) break;
		if (ch == '\\') ignore = true;
		else value.push_back(ch);
	}
	return PREPROC_DIRECTIVE;
}

Token_value getToken() {
	value.clear();
	char ch;
	if (!input->get(ch)) return curr_tok = END;
	switch(ch) {
		case EOL: case SEPARATOR:
			value.push_back(ch);
			return curr_tok = Token_value(ch);
		case COMMENT:
			return curr_tok = processComment();
		case STRING_LITERAL: case CHAR:
			return curr_tok = processLiteral(Token_value(ch));
		case PREPROC_DIRECTIVE:
			return curr_tok = processDirective();
		default:
			if (isalpha(ch) || ch == '_')
				curr_tok = WORD;
			else if (isdigit(ch))
				curr_tok = NUMBER;
			else if (isspace(ch)) {
				do {
					value.push_back(ch);
				}
				while(input->get(ch) && isspace(ch));
			}
			else {
				value.push_back(ch);
				return curr_tok = CONTROL;
			}

			input->putback(ch);
			setValue();
			return curr_tok;
	}
}

std::map<std::string, unsigned> includies;
std::string sys_root = "/usr/include/c++/4.8.2/";

std::string find_file(const std::string& directive) {
	std::string include("include");
	size_t pos = directive.find(include);
	if ( pos != std::string::npos ) {
		size_t len = directive.length();
		size_t start = pos + include.length();
		while(start < len) {
			if (isspace(directive.at(start))) ++start;
			else break;
		}
		if (start < len) {
			std::string arg = directive.substr(start);
			char stop = (arg[0] == '<') ? '>' : '"';
			pos = arg.find(stop, 1);
			if (pos != std::string::npos) {
				std::string name = arg.substr(1, pos - 1);
				return ((stop == '"') ? "./" : sys_root ) + name;
			}
		}
	}
	return "";
}


void scan(const std::string& filename, unsigned level = 0) {
	// read the file
	std::ifstream file(filename.c_str());
	if (file.is_open()) {
		std::istream* tmp = input;
		input = &file;
		typedef std::vector<std::string> vstring;
		vstring depends;
		std::string name;
		while(getToken() != END) {
			if (curr_tok == PREPROC_DIRECTIVE) {
				name = find_file(value);
				if (!name.empty()) depends.push_back(name);
			}
		}
		input = tmp;
		for (vstring::iterator iter = depends.begin(), end = depends.end(); iter != end; ++iter) {
			for (unsigned i = 0; i < level; ++i) std::cout << "\t";
			std::cout << *iter << "\n";
			if ( includies[ *iter ]++ == 0 ) {
				scan( *iter, level + 1 );
			}
		}
	}
}


int main(int argc, char* argv[]) {
	if (argc > 1) {
		std::string name(argv[1]);
		std::cout << name << "\n";
		scan(name, 1);
	}
	return 0;
}
