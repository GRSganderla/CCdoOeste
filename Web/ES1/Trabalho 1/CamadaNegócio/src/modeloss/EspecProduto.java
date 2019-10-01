package modeloss;

import java.util.ArrayList;

public class EspecProduto {

	private String modelo;
	private String tipoProd;
	private String material;
	private float preco;
	private int quant;
	
	public EspecProduto(ArrayList<String> p) {
		
		modelo = p.get(0);
		tipoProd = p.get(1);
		material = p.get(2);
		preco = Float.parseFloat(p.get(3));
		quant = Integer.parseInt(p.get(4));
	}
	
	public EspecProduto() {
	}

	public float getPreco() {
		return preco;
	}

	public void setPreco(float preco) {
		this.preco = preco;
	}

	public int getQuant() {
		return quant;
	}

	public void setQuant(int quant) {
		this.quant = quant;
	}

	public String getModelo() {
		return modelo;
	}
	public void setModelo(String modelo) {
		this.modelo = modelo;
	}
	public String getTipoProd() {
		return tipoProd;
	}
	public void setTipoProd(String tipoProd) {
		this.tipoProd = tipoProd;
	}
	public String getMaterial() {
		return material;
	}
	public void setMaterial(String material) {
		this.material = material;
	}
	public float getPrecos() {
		return preco;
	}
	public void setPrecos(float precos) {
		this.preco = precos;
	}
	
	
	
}
