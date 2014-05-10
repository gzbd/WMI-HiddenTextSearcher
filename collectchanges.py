#!/usr/bin/python2
import os
from BeautifulSoup import BeautifulSoup
import codecs
import uuid

def get_docs_path():
    docs_path = []
    for root, dirs, files in os.walk('./therev'):
        for file in files:
            if file == 'document.html':
                docs_path.append(os.path.join(root, file))
    return docs_path

def extract_changes(file):
    f = open(file)
    raw_file = f.read()
    f.close()
    soup = BeautifulSoup(raw_file)
    changes = ''
    for node in soup.findAll(type='_DELETED_'):
        if node.string:
            changes = changes + node.string
    return changes

def create_solr_add(changes, url):
    solr_add = """
    <add>
        <field name="id">%ID%</field>
        <field name="changes">%CHANGES%</field>
    </add>
    """
    if not url:
        url = uuid.uuid1()
    solr_add = solr_add.replace("%CHANGES%", changes)
    solr_add = solr_add.replace("%ID%", str(url))
    return solr_add


master_file = open('./therev/master.html')
master_file_raw = master_file.read()
master_soup = BeautifulSoup(master_file_raw)
master_anchors = master_soup.findAll('a')
total_links = open('./links/total', 'r')
total_links_raw = total_links.readlines()
def get_file_url(f):
    for a in master_anchors:
        if a['href'] == os.path.abspath(f):
            href = a.parent.parent.findAll('a')[0]['href']
            f_name = os.path.basename(href)
            for line in total_links_raw:
                if f_name in line:
                    return line

def generate_solr_post():
    solr_post = '<doc>'
    for f in get_docs_path():
        changes = extract_changes(f)
        solr_add = create_solr_add(changes, get_file_url(f))
        solr_post = solr_post + solr_add
    solr_post = solr_post + '</doc>\n'

    output = codecs.open('solr_post.xml', 'w', 'utf-8')
    output.write(solr_post)
    output.close()

generate_solr_post()

master_file.close()
total_links.close()
