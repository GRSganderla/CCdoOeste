package AuxiliarFunctions;

import java.util.ArrayList;
import java.util.HashMap;

public class JObjt {
	private String type;
	private String str_content;
	private double num_content;
	private boolean bool_content;
	private ArrayList <JObjt> array_content;
	private HashMap <String, JObjt> object_content;
	private void init() {
		array_content = new ArrayList <JObjt>();
		object_content = new HashMap <String, JObjt>();
	}
	public JObjt() {
		type = null;
		init();
	}
	public JObjt(String type) {
		this.type = type;
		init();
	}
	public void setString(String value) {
		str_content = value;
		type = "string";
	}
	public String getString() {
		return str_content;
	}
	public void setNumber(double value) {
		num_content = value;
		type = "number";
	}
	public double getNumber() {
		return num_content;
	}
	public void setBoolean(boolean value) {
		bool_content = value;
		type = "boolean";
	}
	public boolean getBoolean() {
		return bool_content;
	}
	public void set(int index, JObjt value) {
		while (array_content.size() <= index) {
			array_content.add(null);
		}
		type = "array";
		array_content.set(index, value);
	}
	public JObjt get(int index) {
		return array_content.get(index);
	}
	public void set(String attr, JObjt value) {
		type = "object";
		object_content.put(attr, value);
	}
	public JObjt get(String attr) {
		return object_content.get(attr);
	}
	public int length() {
		return array_content.size();
	}
	public String getType() {
		return type;
	}
}

