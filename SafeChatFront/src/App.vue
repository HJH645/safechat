<template>
  <div id="app">
    <!-- <img alt="Vue logo" src="./assets/logo.png"> -->
    <!-- <HelloWorld msg="Welcome to Your Vue.js App"/> -->



    <el-row v-show="true">
      <ChatRoom>
      </ChatRoom>
    </el-row>





  </div>
</template>

<script>
// import HelloWorld from './components/HelloWorld.vue'
// import myLogin from './components/ChatLogin.vue'
import ChatRoom from './components/ChatRoom.vue';


export default {
  name: 'App',
  components: {
    // HelloWorld,
    // myLogin,
    ChatRoom
  },
  data: function () {
    return {

    }
  },
  methods: {

  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
