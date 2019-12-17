package unioeste.geral.controle_estoque.bo.especifica;

import java.io.Serializable;
import java.util.ArrayList;

import unioeste.geral.controle_estoque.bo.Pessoa;

public class Cliente implements Serializable {

	public Cliente(int idCliente, Pessoa cliente, ArrayList<Nota> notasVendas) {
		super();
		this.idCliente = idCliente;
		this.cliente = cliente;
		NotasVendas = notasVendas;
	}
	/**
	 * Versão da UID auto-gerada pela classe;
	 */
	private static final long serialVersionUID = 8926146334499154793L;
	private int idCliente;
	private Pessoa cliente;
	private ArrayList<Nota> NotasVendas;
	
	public int getIdCliente() {
		return idCliente;
	}
	public void setIdCliente(int idCliente) {
		this.idCliente = idCliente;
	}
	public Pessoa getCliente() {
		return cliente;
	}
	public void setCliente(Pessoa cliente) {
		this.cliente = cliente;
	}
	public ArrayList<Nota> getNotasCompra() {
		return NotasVendas;
	}
	public void setNotasCompra(ArrayList<Nota> notasCompra) {
		NotasVendas = notasCompra;
	}
	public static long getSerialversionuid() {
		return serialVersionUID;
	}
	
}
