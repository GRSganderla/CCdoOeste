<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Cadastro Produto</title>
</head>
<body>
	
	<h1> Tela de Cadastro </h1>
	<br>
	<form action="ProdutoController" method= "post">
		<br>	
		<h4> Nome Produto  <input type="text" id=Nome name="Nome" > </h4>
		<h4> Descricao  <input type="text" id=Descricao name="Descricao" > Foto <input type="text" id=Foto name="DescriçãoFoto"> </h4>
		<h4> Peso/kg <input type="text" id=Peso name="Peso" > </h4> 
		<h4> Cor <input type="text" id=Cor name="Cor" > </h4>
		<h4> Tipo <input type="text" id=Tipo name="Tipo" > </h4>
		<h4> Modelo <input type="text" id=Modelo name="Modelo" > </h4>
		<h4> Tempo de Fabricação <input type="text" id=tempo name="Tempo"></h4>
		<h4> Materia-prima <input type="text" id=Materia1 name="Materia1" > Quantidade <input type="text" id=Quant1 name="Quant1"> Preço <input type="text" id=preco name="Preço"></h4>
		<br>
		<input type="submit" value="Cadastrar"/>
	</form>
	<form action="MenuAdmin.jsp">
	<input type="submit" value="Sair"></form>
</body>
</html>