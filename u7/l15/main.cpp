#include <iostream>
#include <string>
#include <cctype>
#include <map>

#define STREAM std::istream
/* program
**/
// the programm

enum Token_value {
	PREPROC_DIRECTIVE = '#', WORD,
	COMMENT = '/', STRING_LITERAL = '"', CHAR = '\'',
	SEPARATOR = ';', EOL = '\n',
	NUMBER,	CONTROL, END, SPACE = ' '
};

STREAM *input;
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

std::map<std::string, std::string> defines;

void parseDefine() {
	size_t pos = value.find("define");
	if ( pos != std::string::npos ) {
		size_t len = value.length();
		size_t start = pos + 6;
		while(start < len) {
			if (isspace(value.at(start))) ++start;
			else break;
		}
		if (start < len) {
			std::string subject;
			std::string replace;
			std::string* to = &subject;
			bool changed = false;
			for (size_t i = start, len = value.length(); i < len; ++i ) {
				if (isspace(value.at(i)) && !changed) {
					to = &replace;
					changed = true;
				}
				else to->push_back(value.at(i));
			}
			if (!subject.empty()) defines[subject] = replace;
		}
	}
}


int main() {
	input = &std::cin;
	std::map<std::string, std::string>::const_iterator iter;
	while(getToken() != END) {
		/*std::cout << value << "\t";
		switch(curr_tok) {
			case WORD: std::cout << "WORD"; break;
			case PREPROC_DIRECTIVE: std::cout << "PREPROC_DIRECTIVE"; break;
			case COMMENT: std::cout << "COMMENT"; break;
			case STRING_LITERAL: std::cout << "STRING_LITERAL"; break;
			case CHAR: std::cout << "CHAR"; break;
			case SEPARATOR: std::cout << "SEPARATOR"; break;
			case EOL: std::cout << "EOL"; break;
			case NUMBER: std::cout << "NUMBER"; break;
			case CONTROL: std::cout << "CONTROL"; break;
			case END: break;
		}
		std::cout << "\n";*/
		/*if (curr_tok != COMMENT) {
			if (curr_tok == EOL) std::cout << "\n";
			else {
				std::cout << value << " ";
			}
		}*/
		switch (curr_tok) {
			case WORD:
				iter = defines.find(value);
				if (iter != defines.end()) std::cout << iter->second;
				else std::cout << value;
				break;
			case PREPROC_DIRECTIVE:
				parseDefine();
				break;
			case COMMENT: break; // do not write it to out
			case STRING_LITERAL:
				std::cout << "\"" << value << "\"";
				break;
			case CHAR:
				std::cout << "'" << value << "'";
				break;
			case SEPARATOR: case EOL: case NUMBER: case CONTROL: case END:
				std::cout << value;
				break;
			case SPACE: std::cout << SPACE; break;
			default: break; // nothing to do
		}
	}
	return 0;
}
