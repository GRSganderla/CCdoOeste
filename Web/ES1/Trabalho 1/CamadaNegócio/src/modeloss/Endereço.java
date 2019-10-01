package modeloss;

import java.util.ArrayList;

public class Endereço {

	private String Rua;
	private String Bairro;
	private String Cidade;
	private String Estado;
	private String País;
	
	public Endereço() {
		
	}
	
	public Endereço(ArrayList<String> e) {
		
		Rua = e.get(0);
		Bairro = e.get(1);
		Cidade = e.get(2);
		Estado = e.get(3);
		País = e.get(4);
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

	public String getPaís() {
		return País;
	}

	public void setPaís(String país) {
		País = país;
	}
}
