const { defineConfig } = require('@vue/cli-service')

module.exports = {
  devServer: {
    proxy: {
      '/api': {
        target: 'http://localhost:8081',
        changeOrigin: true,
        pathRewrite: {
          '^/api': ''
        }
      }
    }
  }
}

// module.exports = defineConfig({
//   transpileDependencies: true
// })