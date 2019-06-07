package AuxiliarFunctions;

import AuxiliarFunctions.JObjt;

public class Parser {
	private int index;
	private int error;
	private int length;
	private String src;
	private boolean hasError() {
		return error != -1;
	}
	private boolean reachedEnd() {
		return index >= length;
	}
	private boolean isOver() {
		return hasError() || reachedEnd();
	}
	private char nextChar() {
		if (isOver()) return '\0';
		return src.charAt(index);
	}
	private boolean consumeChar(char chr) {
		if (nextChar() == chr) {
			++ index;
			return true;
		}
		return false;
	}
	private char consumeChar() {
		if (isOver()) {
			return '\0';
		}
		return src.charAt(index++);
	}
	private boolean isSpace(char chr) {
		return chr == ' ' || chr == '\t' || chr == '\n';
	}
	private void consumeSpaces() {
		while (isSpace(nextChar())) {
			consumeChar();
		}
	}
	private boolean consumeToken(char chr) {
		if (consumeChar(chr)) {
			consumeSpaces();
			return true;
		}
		return false;
	}
	private boolean consumeToken(String str) {
		int checkpoint = index;
		for (int i=0, n=str.length(); i<n; ++i) {
			if (!consumeChar(str.charAt(i))) {
				index = checkpoint;
				return false;
			}
		}
		consumeSpaces();
		return true;
	}
	private boolean isDig(char chr) {
		return chr >= '0' && chr <= '9';
	}
	private void throwError() {
		if (!hasError()) {
			error = index;
		}
	}
	private JObjt parseNumber() {
		boolean neg = consumeToken('-');
		if (!isDig(nextChar())) {
			throwError();
			return null;
		}
		String str = "";
		while (isDig(nextChar())) {
			str += consumeChar();
		}
		if (consumeChar('.')) {
			str += '.';
			if (!isDig(nextChar())) {
				throwError();
				return null;
			}
			while (isDig(nextChar())) {
				str += consumeChar();
			}
		}
		JObjt obj = new JObjt();
		if (neg) {
			obj.setNumber(-Double.parseDouble(str));
		} else {
			obj.setNumber(Double.parseDouble(str));
		}
		return obj;
	}
	private JObjt parseBoolean() {
		JObjt result = new JObjt();
		if (consumeToken("true")) {
			result.setBoolean(true);
		} else if (consumeToken("false")) {
			result.setBoolean(false);
		} else {
			throwError();
			return null;
		}
		return result;
	}
	private JObjt parseString() {
		char start = consumeChar();
		if (start != '"' && start != '\'') {
			throwError();
			return null;
		}
		String str = "";
		while (!isOver()) {
			if (consumeToken(start)) {
				JObjt obj = new JObjt();
				obj.setString(str);
				return obj;
			}
			char chr = consumeChar();
			if (chr == '\\') {
				if (consumeChar('n')) {
					str += "\n";
				} else if (consumeChar('\\')) {
					str += "\\";
				} else if (consumeChar('"')) {
					str += "\"";
				} else if (consumeChar('\'')) {
					str += "'";
				} else if (consumeChar('t')) {
					str += "\t";
				} else {
					throwError();
					return null;
				}
			} else {
				str += chr;
			}
		}
		throwError();
		return null;
	}
	private JObjt parseObject() {
		if (!consumeToken('{')) {
			return null;
		}
		JObjt obj = new JObjt("object");
		if (!consumeToken('}')) {
			while (!isOver()) {
				JObjt key = parseString();
				if (hasError() || !consumeToken(':')) {
					throwError();
					return null;
				}
				JObjt value = rootParse();
				if (hasError()) {
					return null;
				}
				obj.set(key.getString(), value);
				if (consumeToken('}')) {
					break;
				}
				if (!consumeToken(',')) {
					throwError();
					return null;
				}
			}
		}
		return obj;
	}
	private JObjt parseArray() {
		if (!consumeToken('[')) {
			throwError();
			return null;
		}
		JObjt obj = new JObjt("array");
		if (consumeToken(']')) {
			return obj;
		}
		while (!isOver()) {
			JObjt item = rootParse();
			if (hasError()) {
				return null;
			}
			obj.set(obj.length(), item);
			if (consumeToken(']')) {
				break;
			}
			if (!consumeToken(',')) {
				throwError();
				return null;
			}
		}
		return obj;
	}
	public Parser() {
		this.src = null;
		this.index = 0;
		this.error = -1;
		this.length = 0;
	}
	public JObjt rootParse() {
		char chr = nextChar();
		if (isDig(chr) || chr == '-') {
			return parseNumber();
		} else if (chr == 't' || chr == 'f') {
			return parseBoolean();
		} else if (chr == '"' || chr == '\'') {
			return parseString();
		} else if (chr == '[') {
			return parseArray();
		} else if (chr == '{') {
			return parseObject();
		}
		return null;
	}
	public JObjt parse(String src) {
		this.src = src;
		this.index = 0;
		this.error = -1;
		this.length = src.length();
		return rootParse();
	}
	public int errorIndex() {
		return error;
	}
}