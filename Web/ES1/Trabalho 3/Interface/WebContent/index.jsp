<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<link rel="stylesheet" type="text/css" href="css/foundation.css">
<title>Consulta</title>
<script type="text/javascript">
var Msg ='<%=session.getAttribute("Alert")%>';
    if (Msg != "No" && Msg != "null") {
 function alertName(){
 alert(Msg);
 } 
 }
 </script> 
 <script type="text/javascript"> window.onload = alertName; </script>
</head>
<body>
        
    <div class="top-bar" style="background-color: orange;">
  		<div class="top-bar-left">
 
 		</div>
	  	<div class="top-bar-right">
		    <ul class="menu">
		      <li><a class="button" href="Transferencia.jsp">Realizar transferência</a></li>
		    </ul>
		 </div>
	</div>


	<div class="grid-container">
	
		<div class="row">
    		<div class="small-6 small-centered text-center columns">
				<h3>Consulta de extrato bancário</h3>
    		</div>
		</div>	

		<form action="ConsultaExtrato" method="post">
								
				<div class="grid-x grid-padding-x">
						
					<div class="medium-6 cell">
						<label>Cliente: 
						<input type="text" name="cliente">							
						</label>
					</div>
					
					<div class="medium-6 cell">
						<label>CPF/CNPJ: 
						<input type="text" name="cpf_cnpj">
						</label>
					</div>
							 
		   			<button type="submit" class="button">Consultar</button>
						
				</div>
				
		</form>

	</div>

</body>
</html>