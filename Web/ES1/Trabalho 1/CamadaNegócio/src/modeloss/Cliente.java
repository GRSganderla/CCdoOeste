package modeloss;

import java.util.ArrayList;

public class Cliente {
	
	private int idCliente = 0;
	private String Nome;
	private String CPF;
	private String CNPJ;
	private String Email;
	private String Senha;
	private String Fones;
	private int Num = 0;
	private String Complemento;
	private String CEP;
	private int Endereco;
	
	public int getEndereco() {
		return Endereco;
	}

	public void setEndereco(int endereco) {
		Endereco = endereco;
	}

	public Cliente() {
		
	}
	
	public Cliente(ArrayList<String> Cliente) {
		
		this.idCliente = Integer.parseInt(Cliente.get(0));
		this.Nome = Cliente.get(1);
		this.CPF = Cliente.get(3);
		this.CNPJ = Cliente.get(2);
		this.Email = Cliente.get(4);
		this.Senha = Cliente.get(5);
		this.Num = Integer.parseInt(Cliente.get(6));
		this.Complemento = Cliente.get(7);
		this.CEP = Cliente.get(8);
		this.Endereco = Integer.parseInt(Cliente.get(9));
	}

	public int getIdCliente() {
		return idCliente;
	}

	public void setIdCliente(int idCliente) {
		this.idCliente = idCliente;
	}

	public String getNome() {
		return Nome;
	}

	public void setNome(String nome) {
		Nome = nome;
	}

	public String getCPF() {
		return CPF;
	}

	public void setCPF(String cPF) {
		CPF = cPF;
	}

	public String getCNPJ() {
		return CNPJ;
	}

	public void setCNPJ(String cNPJ) {
		CNPJ = cNPJ;
	}

	public String getEmail() {
		return Email;
	}

	public void setEmail(String email) {
		Email = email;
	}

	public String getSenha() {
		return Senha;
	}

	public void setSenha(String senha) {
		Senha = senha;
	}

	public int getNum() {
		return Num;
	}

	public void setNum(int num) {
		Num = num;
	}

	public String getComplemento() {
		return Complemento;
	}

	public void setComplemento(String complemento) {
		Complemento = complemento;
	}

	public String getCEP() {
		return CEP;
	}

	public void setCEP(String cEP) {
		CEP = cEP;
	}
	
	public String getFones() {
		return Fones;
	}

	public void setFones(String fone) {
		Fones = fone;
	}
}

