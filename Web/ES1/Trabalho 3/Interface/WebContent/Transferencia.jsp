<%@ page language="java" contentType="text/html; charset=utf-8"
	pageEncoding="utf-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<link rel="stylesheet" type="text/css" href="css/foundation.css">
<title>Transferencia</title>
</head>
<body>

    <div class="top-bar" style="background-color: orange;">
  		<div class="top-bar-left">
 
 		</div>
	  	<div class="top-bar-right">
		    <ul class="menu">
		      <li><a class="button" href="index.jsp">Voltar</a></li>
		    </ul>
		 </div>
	</div>

	<div class="grid-container">


		<div class="row">
			<div class="small-6 small-centered text-center columns">
				<h3>Transferência bancária entre contas</h3>
			</div>
		</div>

		<form action="TransferenciaBancaria" method="post">

			<div class="grid-x grid-padding-x">

				<div class="medium-6 cell">
					<label>Cliente (Correntista): <input type="text"
						name="cliente">
					</label>
				</div>

				<div class="medium-6 cell">
					<label>CPF/CNPJ: <input type="text" name="cpfCnpj">
					</label>
				</div>

				<div class="medium-6 cell">
					<label>Conta: <input type="number" name="conta">
					</label>
				</div>

				<div class="medium-6 cell">
					<label>Data de transferência: <input type="date"
						name="data">
					</label>
				</div>

			</div>

			<p style="margin-left:5px">Favorecido (Conta a transferir)</p>

			<div class="grid-x grid-padding-x">

				<div class="medium-4 cell">
					<label>Cod. Banco: <input type="number" name="codBanco">
					</label>
				</div>

				<div class="medium-4 cell">
					<label>Nro. Agencia: <input type="number" name="nroAgencia">
					</label>
				</div>

				<div class="medium-4 cell">
					<label>Nro. Conta: <input type="number" name="nroConta">
					</label>
				</div>

				<div class="medium-6 cell">
					<label>Nome Favorecido: <input type="text" name="favorecido">
					</label>
				</div>

				<div class="medium-6 cell">
					<label>CPF/CNPJ: <input type="text" name="cpfCnpj_fav">
					</label>
				</div>

				<div class="medium-12 cell">
					<label>Valor de transferência R$: <input type="number" name="valorTransf" step="0.01">
					</label>
				</div>

				<button type="submit" class="button">Registrar Transfêrencia Bancária</button>

			</div>

		</form>

	</div>


</body>
</html>