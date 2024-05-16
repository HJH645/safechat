import Vue from 'vue'
import App from './App.vue'
import ElementUI from 'element-ui'
import Vuex from 'vuex'
import store from './store'

import 'element-ui/lib/theme-chalk/index.css';

Vue.use(ElementUI)
Vue.config.productionTip = false
Vue.use(Vuex)


new Vue({
  render: h => h(App),
  store
}).$mount('#app')
