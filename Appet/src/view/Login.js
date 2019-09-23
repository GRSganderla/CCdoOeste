import React, {Fragment} from 'react';
import {Component} from 'react';
import {
  StyleSheet,
  ScrollView,
  View,
  Text,
  StatusBar,
  TouchableOpacity,
} from 'react-native';

export default class Login extends Component{

  render(){
    return(
      <View style = {styles.container}>
        <TouchableOpacity style = {styles.buttonAcessar}>
          <Text>Fazer login com o Facebook</Text>
        </TouchableOpacity>
        <TouchableOpacity style = {styles.buttonAcessar}>
          <Text>Fazer login com o Google</Text>
        </TouchableOpacity>
        <TouchableOpacity style = {styles.buttonAcessar} onPress={() => this.props.navigation.navigate('Menu')}>
          <Text>Fazer login como convidado</Text>
        </TouchableOpacity>
      </View>
    )
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    paddingHorizontal: 15
  },

  buttonAcessar: {
    width: 300,
    borderRadius: 25,
    marginVertical: 10,
    backgroundColor: '#6699ff',
    textAlign: 'center',
    padding: 10
  },

  texto: {
    flex: 1,
    fontSize: 18,
    color: '#FFFFFF',
    textAlign: 'center'
  }
});
