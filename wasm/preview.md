---
theme: default
title: C/WASM USB Descriptor Demo
colorSchema: dark
---

<script setup lang="ts">
import UsbDescriptorDemo from '../components/UsbDescriptorDemo.vue'
import wasmUrl from '../public/wasm/usb_descriptor.wasm?url'
</script>

<UsbDescriptorDemo :wasm-url="wasmUrl" />
