<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>Consultar e Alterar Clinte</title>
</head>
<body>
	<h2>Dados do Cliente:</h2>
	
	<form action="AlterarController" method="post">
	<h4>Nome: <%= request.getAttribute("Nome")%></h4>
	<input type="hidden" name="Nome" value="<%out.print(request.getAttribute("Nome"));%>"/>
	<h4>CPF: <%= request.getAttribute("CPF")%> CNPJ: <%= request.getAttribute("CNPJ") %></h4>
	<input type="hidden" name="CPF" value="<%out.print(request.getAttribute("CPF"));%>"/>
	<input type="hidden" name="CNPJ" value="<%out.print(request.getAttribute("CNPJ"));%>"/>
	<h4>Email: <%= request.getAttribute("Email") %></h4>
	<input type="hidden" name="Email" value="<%out.print(request.getAttribute("Email"));%>"/>
	<h4>Senha: <input type="text" id=Senha name="S" value="<%= request.getAttribute("Senha") %>"></h4>
	<h4>CEP: <input type="text" id=CEP name="CEP" value="<%= request.getAttribute("CEP") %>"></h4>
	<h4>Rua: <input type="text" id=Rua name="R" value="<%= request.getAttribute("Rua") %>"> Número: <input type="text" id=num name="N" value="<%= request.getAttribute("Numero") %>"></h4>
	<h4>Bairro: <input type="text" id=Bairro name="Bai" value="<%= request.getAttribute("Bairro") %>"> Complemento: <input type="text" id=Complemento name="Co" value= "<%= request.getAttribute("Complemento") %>"></h4>
	<h4>Cidade: <input type="text" id=Cidade name="Cid" value="<%= request.getAttribute("Cidade")%>"> Estado: <input type="text" id=estado name="E" value="<%= request.getAttribute("Estado") %>"> País: <input type="text" id=pais name="P" value="<%= request.getAttribute("País") %>"></h4>
	<input type="hidden" name="ID" value="<%out.print(request.getAttribute("clienteId"));%>">
	<h4><input type="submit" value="Alterar"></h4>
	</form>
	
	<form action="ExcluirClienteController" method= "post">
	<input type="hidden" name="clienteId" value="<%out.print(request.getAttribute("clienteId"));%>"/>
	<h4><input type="submit" value="Excluir"></h4>
	</form>
	<form action="VoltarMenuController" method= "post">
	<input type="hidden" name="clienteId" value="<%out.print(request.getAttribute("clienteId"));%>"/>
	<h4><input type="submit" value="Sair"></h4>
	</form>
		
</body>
</html>