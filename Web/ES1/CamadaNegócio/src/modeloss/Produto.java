package modeloss;

public class Produto {
	
	private int idProduto;
	private int TempoFab;
	private String nome;
	private String descricao;
	private float peso;
	private String cor;
	private int idTipo;
	private int idMode;
	
	public int getIdTipo() {
		return idTipo;
	}
	public void setIdTipo(int idTipo) {
		this.idTipo = idTipo;
	}
	public int getIdMode() {
		return idMode;
	}
	public void setIdMode(int idMode) {
		this.idMode = idMode;
	}
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public String getDescricao() {
		return descricao;
	}
	public int getIdProduto() {
		return idProduto;
	}
	public void setIdProduto(int idProduto) {
		this.idProduto = idProduto;
	}
	public int getTempoFab() {
		return TempoFab;
	}
	public void setTempoFab(int tempoFab) {
		TempoFab = tempoFab;
	}
	public void setDescricao(String descricao) {
		this.descricao = descricao;
	}
	public float getPeso() {
		return peso;
	}
	public void setPeso(float peso) {
		this.peso = peso;
	}
	public String getCor() {
		return cor;
	}
	public void setCor(String cor) {
		this.cor = cor;
	}
	
	
}
