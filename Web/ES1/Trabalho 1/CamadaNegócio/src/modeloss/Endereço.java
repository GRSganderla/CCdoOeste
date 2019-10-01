package modeloss;

import java.util.ArrayList;

public class Endere�o {

	private String Rua;
	private String Bairro;
	private String Cidade;
	private String Estado;
	private String Pa�s;
	
	public Endere�o() {
		
	}
	
	public Endere�o(ArrayList<String> e) {
		
		Rua = e.get(0);
		Bairro = e.get(1);
		Cidade = e.get(2);
		Estado = e.get(3);
		Pa�s = e.get(4);
	}
	
	public String getRua() {
		return Rua;
	}

	public void setRua(String rua) {
		Rua = rua;
	}

	public String getBairro() {
		return Bairro;
	}

	public void setBairro(String bairro) {
		Bairro = bairro;
	}

	public String getCidade() {
		return Cidade;
	}

	public void setCidade(String cidade) {
		Cidade = cidade;
	}

	public String getEstado() {
		return Estado;
	}

	public void setEstado(String estado) {
		Estado = estado;
	}

	public String getPa�s() {
		return Pa�s;
	}

	public void setPa�s(String pa�s) {
		Pa�s = pa�s;
	}
}
